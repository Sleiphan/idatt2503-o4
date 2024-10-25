#include "hex.hpp"

char bit4_to_hex_digit(unsigned char bit_4)
{
  bit_4 &= 0xF;
  bit_4 += 7 * (bit_4 > 9);
  bit_4 += '0';
  return bit_4;
}

unsigned char hex_digit_to_bit4(char hex_digit)
{
  hex_digit -= '0';
  hex_digit -= 7 * (hex_digit > 9);
  hex_digit &= 0xF;
  return hex_digit;
}

unsigned char hex_digit_to_byte(char hex_MSB, char hex_LSB)
{
  unsigned char MSB = hex_digit_to_bit4(hex_MSB);
  unsigned char LSB = hex_digit_to_bit4(hex_LSB);

  MSB &= 0xF;
  LSB &= 0xF;

  MSB <<= 4;

  return MSB + LSB;
}

int hex2bytes(unsigned char *dst, const char *hex, size_t hex_length)
{
  hex_length &= (size_t)(-2);

  const char *src_it = hex;
  unsigned char *dst_it = dst;
  const char *src_end = hex + hex_length;

  for (; src_it < src_end; ++dst_it)
  {
    const char MSB = *(src_it++);
    const char LSB = *(src_it++);

    *dst_it = hex_digit_to_byte(MSB, LSB);
  }

  return dst_it - dst;
}

int bytes2hex(char *dst, const unsigned char *bytes, const size_t num_bytes)
{
  char *dst_it = dst;

  for (const unsigned char *src_it = bytes; src_it < bytes + num_bytes; ++src_it)
  {
    *(dst_it++) = bit4_to_hex_digit((*src_it & 0xF0) >> 4);
    *(dst_it++) = bit4_to_hex_digit(*src_it & 0xF);
  }

  return dst_it - dst;
}