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