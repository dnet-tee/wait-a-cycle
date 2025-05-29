#include <msp430.h>
#include <stdio.h>
#include <sancus/sm_support.h>
#include <sancus_support/sm_io.h>
#include <sancus_support/timer.h>
#include <sancus_support/tsc.h>

typedef tsc_t secret_data_t;

typedef struct
{
    char cipher[sizeof(secret_data_t)];
    char tag[SANCUS_TAG_SIZE];
} CipherData;

typedef unsigned nonce_t;

void exit_success(void);

/* ======== HELLO WORLD SM ======== */

DECLARE_SM(hello, 0x1234);

void SM_ENTRY(hello) hello_wrap(tsc_t* data, nonce_t ad, CipherData* cipher)
{
    sancus_wrap(&ad, sizeof(ad), data, sizeof(*data),
                       &cipher->cipher, &cipher->tag);
}

int SM_ENTRY(hello) super_secure_ecall(nonce_t ad, CipherData* cipher)
{
    tsc_t cmd;
    if (sancus_unwrap(&ad, sizeof(ad), &cipher->cipher, sizeof(cipher->cipher), &cipher->tag, &cmd))
    {
        pr_info1("Data successfully unwrapped! cmd = %u\n", cmd);
        if (cmd !=0)
        {
            pr_info("should never see this!");
        }
    }
    return 0;
}

/* ======== UNTRUSTED CONTEXT ======== */

int main()
{
    msp430_io_init();

    // sancus_enable(&attacker);
    // pr_sm_info(&attacker);
    sancus_enable(&hello);
    pr_sm_info(&hello);

    nonce_t no = 0xabcd;
    uint tsc1, tsc2;
    timer_tsc_start();
    tsc1 = timer_tsc_end();
    pr_info1("tsc overhead: %u\n", tsc1);
    tsc_t data = 0x5678;
    CipherData correct_cipher = { 0 };
    hello_wrap(&data, no, &correct_cipher);
    char* correct_tag = correct_cipher.tag;
    dump_buf((uint8_t*)correct_tag, SANCUS_TAG_SIZE, "  Correct tag");
    dump_buf((uint8_t*)correct_cipher.cipher, SANCUS_KEY_SIZE, "  Correct cipher");
    
    // Fill the cipher with incorrect arbitrary data
    CipherData cipher = { .cipher = "\x00\x00\x00\x00\x00\x00\x00\x00",
                           #if SANCUS_KEY_SIZE == 8
                                .tag = "\x00\x00\x00\x00\x00\x00\x00\x00"
                           #else
                                .tag = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
                           #endif
                        };

    // Put the correct cipher in the first 8 bytes
    for( int i = 0; i < 8; i++ ){
        cipher.cipher[i] = correct_cipher.cipher[i];
    }
    dump_buf((uint8_t*)cipher.cipher, SANCUS_KEY_SIZE, "  Copy correct cipher");


    for( int i = 0; i < SANCUS_TAG_SIZE/2; i++ ){
        cipher.tag[2*i] = correct_tag[2*i];
        cipher.tag[2*i+1] = correct_tag[2*i+1];
        
        timer_tsc_start();
        super_secure_ecall(no, &cipher);
        tsc2 = timer_tsc_end();
        printf("Time to verify if only %d/%d words correct: %u, tsc overhead: %u\n", i+1, SANCUS_TAG_SIZE/2, tsc2, tsc1);
    }
    // ======== WITHOUT INFO ==========

    // CipherData cipher_guess = { .cipher = "\x78\x56\x78\x56\x78\x56\x78\x56",
    //                     .tag = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" };

    // for( int i = 0; i < 256; i++ ){
    //     cipher_guess.tag[0] = i;
    //     for( int j = 0; j < 256; j++ ){
    //         cipher_guess.tag[1] = j;
            
    //         timer_tsc_start();
    //         super_secure_ecall(no, &cipher_guess);
    //         tsc2 = timer_tsc_end();
    //         if( tsc2 > 2553 ){
    //             dump_buf((uint8_t*)cipher_guess.tag, 16, "  Guessed tag");
    //             pr_info1("Time to verify guess: %u\n", tsc2);
    //         }
    //     }
    //     pr_info1("Finished %d/255\n", i);
    // }

    // exit_success();
}

void exit_success(void)
{
    pr_info("SM disabled; all done!\n\n");
    FINISH();
}
