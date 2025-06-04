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

// Function using the unwrap primitive to verify and decrypt some data received from a third party.
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

    // Loop that will show the timing difference of the unwrap primitive.
    // Words of the tag are made correct one by one.
    for( int i = 0; i < SANCUS_TAG_SIZE/2; i++ ){
        cipher.tag[2*i] = correct_tag[2*i];
        cipher.tag[2*i+1] = correct_tag[2*i+1];
        
        timer_tsc_start();
        super_secure_ecall(no, &cipher);
        tsc2 = timer_tsc_end();
        printf("Time to verify if only %d/%d words correct: %u, tsc overhead: %u\n", i+1, SANCUS_TAG_SIZE/2, tsc2, tsc1);
    }

    // For an end-to-end attack, we refer to the auth-ex-break example.
    exit_success();
}

void exit_success(void)
{
    pr_info("SM disabled; all done!\n\n");
    FINISH();
}
