#include "galois_field.h"

uint8_t gf_mult(uint16_t a, uint16_t b)
{
  const uint16_t mod = 0x11b;

  uint16_t product = 0;

  while (b > 0)
  {
    if (b & 1)
      product ^= a;

    a <<= 1;

    if (a & 0x100)
      a ^= mod;

    b >>= 1;
  }

  return product & 0xff;
}