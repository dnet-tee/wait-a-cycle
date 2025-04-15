#include <sancus_support/sm_io.h>
#include <sancus_support/timer.h>
#include <stdint.h>

int secure_memcmp(const uint8_t *s1, const uint8_t *s2, int size)
{
  int res = 0;
  int first = 1;
  for (int i = 0; i < size; i++)
  {
    if (first == 1 && s1[i] > s2[i])
    {
      res = 1;
      first = 0;
    }
    else if (first == 1 && s1[i] < s2[i])
    {
      res = -1;
      first = 0;
    }
  }
  return res;
}

int main()
{
    int tsc1, tsc2;
    msp430_io_init();

    /* First measure TSC function overhead */
    timer_tsc_start();
    tsc1 = timer_tsc_end();

    /* Now measure the operation of interest */
    uint8_t arr[5] = {0x05, 0x65, 0xe8, 0x3c, 0xab};
    uint8_t arr2[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
    int res;
    timer_tsc_start();
    res = secure_memcmp(arr, arr2, 5);
    tsc2 = timer_tsc_end();
    pr_info3("comparison (%d/5 bytes correct) with result: %d, took %d cycles\n", 0, res, tsc2-tsc1);

    for ( int i = 0; i < 5; i++ )
    {
        for ( uint8_t j = 0; j < 255; j++ )
        {
            arr2[i] = j;
            timer_tsc_start();
            res = secure_memcmp(arr, arr2, 5);
            tsc2 = timer_tsc_end();
            if( tsc2 - tsc1 >= 57 + (i+1)*19 || (i == 4 && tsc2 - tsc1  == 138 )){
              pr_info3("comparison (%d/5 bytes correct) with result: %d, took %d cycles\n", i+1, res, tsc2-tsc1);
              break;
            }
        }
    }

    for( int i = 0; i < 5; i++ )
    {
        pr_info2("arr2[%d] = %d\n", i, arr2[i]);
    }
    
    FINISH();
    ASSERT(0 && "should never reach here");
}
