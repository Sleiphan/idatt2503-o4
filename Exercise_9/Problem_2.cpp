#include <stdint.h>
#include <stdio.h>
#include <typeinfo>

int binary_LFSR(int seed, int mask)
{
  int8_t new_bit = 0;

  const int seed_xor = seed & mask;

  for (unsigned int mask_it = 1; mask_it != 0; mask_it <<= 1)
  {
    int8_t val = (seed_xor & mask_it) != 0;
    new_bit ^= val;
  }

  seed <<= 1;
  seed |= new_bit;

  return seed;
}

int find_period_of_binary_LFSR(int seed, int mask, int limit)
{
  int period = 0;

  int val = seed;

  for (int i = 0; i < limit & !period; ++i)
  {
    val = binary_LFSR(val, mask);
    val &= 0b0'1111;
    period = (i + 1) * (val == seed);
  }

  return period;
}

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)       \
  ((byte) & 0x80 ? '1' : '0'),     \
      ((byte) & 0x40 ? '1' : '0'), \
      ((byte) & 0x20 ? '1' : '0'), \
      ((byte) & 0x10 ? '1' : '0'), \
      ((byte) & 0x08 ? '1' : '0'), \
      ((byte) & 0x04 ? '1' : '0'), \
      ((byte) & 0x02 ? '1' : '0'), \
      ((byte) & 0x01 ? '1' : '0')

int main()
{
  const int seed_1 = 0b0000'1000;
  const int seed_2 = 0b0000'0011;
  const int xor_mask_1 = 0b0'1111;
  const int xor_mask_2 = 0b0'1001;

  int period_1 = find_period_of_binary_LFSR(seed_1, xor_mask_1, 100);
  printf("LFSR-period of seed " BYTE_TO_BINARY_PATTERN " is %d\n", BYTE_TO_BINARY(seed_1), period_1);

  int period_2 = find_period_of_binary_LFSR(seed_2, xor_mask_1, 100);
  printf("LFSR-period of seed " BYTE_TO_BINARY_PATTERN " is %d\n", BYTE_TO_BINARY(seed_2), period_2);

  int period_3 = find_period_of_binary_LFSR(seed_1, xor_mask_2, 100);
  printf("LFSR-period of seed " BYTE_TO_BINARY_PATTERN " with mask " BYTE_TO_BINARY_PATTERN " is %d\n", BYTE_TO_BINARY(seed_1), BYTE_TO_BINARY(xor_mask_2), period_3);

  int period_4 = find_period_of_binary_LFSR(seed_2, xor_mask_2, 100);
  printf("LFSR-period of seed " BYTE_TO_BINARY_PATTERN " with mask " BYTE_TO_BINARY_PATTERN " is %d\n", BYTE_TO_BINARY(seed_2), BYTE_TO_BINARY(xor_mask_2), period_4);
}
