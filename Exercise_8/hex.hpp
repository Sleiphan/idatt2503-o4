#ifndef CUSTOM_HEX_FUNCTIONS
#define CUSTOM_HEX_FUNCTIONS

#include <stdlib.h>

char bit4_to_hex_digit(unsigned char bit_4);

unsigned char hex_digit_to_bit4(char hex_digit);

unsigned char hex_digit_to_byte(char hex_MSB, char hex_LSB);

int hex2bytes(unsigned char *dst, const char *hex, size_t hex_length);

int bytes2hex(char *dst, const unsigned char *bytes, const size_t num_bytes);

#endif // CUSTOM_HEX_FUNCTIONS