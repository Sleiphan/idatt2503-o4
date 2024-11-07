#include "galois_field.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

void load_field(uint8_t target[256][256], const char *file_path)
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(file_path, "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  for (int y = 0; y < 256; ++y)
  {
    read = getline(&line, &len, fp);
    size_t idx = 0;

    for (int x = 0; x < 256; ++x)
    {
      while (line[idx] == ' ')
        ++idx;

      target[y][x] = atoi(&line[idx]);

      while (line[idx] >= '0' & line[idx] <= '9')
        ++idx;
    }
  }

  fclose(fp);
}

bool verify_gf_mult()
{
  const char file_path[] = "./Exercise_9/mul_table.txt";

  uint8_t target[256][256];

  load_field(target, file_path);

  bool works = true;

  for (int y = 0; y < 256; ++y)
    for (int x = 0; x < 256; ++x)
      works &= gf_mult(y, x) == target[y][x];

  return works;
}

void find_multiplicative_inverses(uint8_t dst[256], const uint8_t table[256][256])
{
  memset(dst, 0, 256);
  for (int y = 0; y < 256; ++y)
    for (int x = 0; x < 256; ++x)
      if (table[y][x] == 1)
        dst[y] = x;
}

bool check_commutative()
{
  bool commutative = true;

  for (int y = 0; y < 256; ++y)
    for (int x = 0; x < 256; ++x)
    {
      uint8_t ab = gf_mult(x, y);
      uint8_t ba = gf_mult(y, x);
      commutative &= ab == ba;
    }

  return commutative;
}

bool check_associative()
{
  bool commutative = true;

  for (int c = 0; c < 256; ++c)
    for (int b = 0; b < 256; ++b)
      for (int a = 0; a < 256; ++a)
      {
        uint8_t ab_c = gf_mult(gf_mult(a, b), c);
        uint8_t a_bc = gf_mult(a, gf_mult(b, c));
        commutative &= ab_c == a_bc;
      }

  return commutative;
}

bool check_distributive()
{
  bool distributive = true;

  for (int c = 0; c < 256; ++c)
    for (int b = 0; b < 256; ++b)
      for (int a = 0; a < 256; ++a)
      {
        uint8_t a_bc = gf_mult(a, b ^ c);
        uint8_t ab_ac = gf_mult(a, b) ^ gf_mult(a, c);
        distributive &= a_bc == ab_ac;
      }

  return distributive;
}

int find_perfect_generator()
{
  uint8_t generator = 0;

  for (int g = 2; g < 256 & !generator; ++g)
  {
    uint32_t taken_indices[8];
    memset(taken_indices, 0xFFFFFFFF, sizeof(taken_indices));
    taken_indices[0] ^= 1;

    int current_generator_val = g;

    for (int i = 1; i < 256; ++i)
    {
      const int major = current_generator_val >> 5;
      const int minor = current_generator_val & 31;

      taken_indices[major] ^= 1 << minor;

      current_generator_val = gf_mult(current_generator_val, g);
    }

    bool valid_generator = true;
    for (uint32_t i : taken_indices)
      valid_generator &= i == 0;

    if (valid_generator)
      generator = g;
  }

  return generator;
}

int problem_3_demo()
{
  printf("Verification of gf_mult() %s\n", (verify_gf_mult() ? "successful" : "FAILED"));

  const char file_path[] = "./Exercise_9/mul_table.txt";
  uint8_t file_data[256][256];
  load_field(file_data, file_path);

  uint8_t multiplicatives[256];
  find_multiplicative_inverses(multiplicatives, file_data);
  for (int i = 0; i < 256; ++i)
    printf("The multiplicative inverse of %d is %d\n", i, multiplicatives[i]);

  printf("gf_mult() is %scommutative\n", (check_commutative() ? "" : "not "));
  printf("gf_mult() is %sassociative\n", (check_associative() ? "" : "not "));
  printf("gf_mult() is %sdistributive\n", (check_distributive() ? "" : "not "));
  printf("A generator that fulfill all the requirements in task 3.d) is: %d\n", find_perfect_generator());

  return 0;
}

int main()
{
  problem_3_demo();
  return 0;
}
