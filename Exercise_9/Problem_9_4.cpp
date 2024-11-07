#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "galois_field.h"

uint8_t MODULO_INVERSE_LT[256];

void fill_modulo_inverse_lt()
{
  memset(MODULO_INVERSE_LT, 0, sizeof(MODULO_INVERSE_LT));
  for (int i = 1; i < 256; ++i)
    for (int g = 1; g < 256 & !MODULO_INVERSE_LT[i]; ++g)
      MODULO_INVERSE_LT[i] = g * (gf_mult(i, g) == 1);
}

int ctr_key_gen(const uint8_t counter_val, const uint8_t secret_key, const uint8_t nonce)
{
  // Combine counter value and nonce
  uint8_t key = ((nonce & 0xF) << 4) | (counter_val & 0xF);

  // Use multiplicative inverse of the result.
  key = MODULO_INVERSE_LT[key];

  // XOR the inverse with the key
  key ^= secret_key;

  return key;
}

void print_first_n_keys(const uint8_t secret_key, const uint8_t nonce, const int num_keys)
{
  for (int i = 0; i < num_keys; ++i)
    printf("Key %d: %d\n", i, ctr_key_gen(i, secret_key, nonce));
}

int find_period(const uint8_t secret_key, const uint8_t nonce, const int limit)
{
  const uint8_t target_key = ctr_key_gen(0, secret_key, nonce);
  uint8_t current_key = target_key + 1;

  int period = 0;

  while (current_key != target_key & period < limit)
    current_key = ctr_key_gen(++period, secret_key, nonce);

  if (period >= limit)
    period = -1;

  return period;
}

void print_keygen_period(const uint8_t secret_key, const uint8_t nonce)
{
  int period = find_period(secret_key, nonce, 1000);
  printf("Found period [%d] of the key stream using secret key [%d] and nonce [%d]\n", period, secret_key, nonce);
}

void problem_4_demo()
{
  fill_modulo_inverse_lt();

  const uint8_t secret_key = 0b0100'1010;
  const uint8_t nonce = 0b0110;

  print_first_n_keys(secret_key, nonce, 4);
  print_keygen_period(secret_key, nonce);
}

int main()
{
  problem_4_demo();
  return 0;
}