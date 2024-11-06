#include "hex.hpp"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

template <typename T>
void int_to_bytes(unsigned char *bytes, const T number)
{
  for (int i = 0; i < sizeof(T); ++i)
    bytes[i] = number >> ((sizeof(T) - i - 1) * 8) & 0xFF;
}

void affine_encryption(unsigned char *string, const __uint128_t multiplier, const __uint128_t shift, const size_t text_len)
{
  const unsigned char *end = string + text_len;

  for (unsigned char *it = string; it != end; ++it)
    *it = (*it * multiplier + shift) & 0xFF;
}

int main()
{
  const __uint128_t K1 = ((__uint128_t)0x0123456789ABCDEFULL << 64) | 0x0123456789ABCDEFULL;
  const __uint128_t K2 = ((__uint128_t)0x1123456789ABCDEFULL << 64) | 0x0123456789ABCDEFULL;

  const __uint128_t x1 = ((__uint128_t)0x010000000000000ULL << 64) | 0x0000000000000000ULL;
  const __uint128_t x2 = ((__uint128_t)0x020000000000000ULL << 64) | 0x0000000000000000ULL;

  unsigned char bytes[sizeof(__uint128_t)];
  int_to_bytes(bytes, x1);

  affine_encryption(bytes, K1, K2, sizeof(__uint128_t));

  char hexes[sizeof(__uint128_t) * 2 + 1];
  bytes2hex(hexes, bytes, sizeof(__uint128_t));
  hexes[sizeof(__uint128_t) * 2] = '\0';

  printf("%s\n", hexes);

  return 0;
}
