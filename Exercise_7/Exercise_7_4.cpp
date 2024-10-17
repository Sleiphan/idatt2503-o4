#include <stdio.h>
#include <string.h>

void ceasar_shift(char *text, const int shift)
{
  static const int LETTERS_IN_ALPHABET = 26;

  const size_t text_len = strlen(text);
  const char *end = text + text_len;

  const char big_a = 'A';
  const char small_a = 'a';

  for (char *it = text; it != end; ++it)
  {
    const char &base = *it >= small_a ? small_a : big_a;
    char letter_idx = *it - base;
    char new_letter_idx = (letter_idx + shift) % LETTERS_IN_ALPHABET;
    *it = new_letter_idx + base;
  }
}

void affine_encryption(char *text, const int multiplier, const int shift)
{
  static const int LETTERS_IN_ALPHABET = 26;

  const size_t text_len = strlen(text);
  const char *end = text + text_len;

  const char big_a = 'A';
  const char small_a = 'a';

  for (char *it = text; it != end; ++it)
  {
    const char &base = *it >= small_a ? small_a : big_a;
    int letter_idx = *it - base;
    int new_letter_idx = (letter_idx * multiplier + shift) % LETTERS_IN_ALPHABET;
    *it = new_letter_idx + base;
  }
}

int find_modulo_inverse(const int number, const int modulo, const int max_check)
{
  for (int i = 2; i < max_check; ++i)
    if ((number * i) % modulo == 1)
      return i;

  return -1;
}

void affine_decryption(char *text, const int multiplier, const int shift)
{
  static const int LETTERS_IN_ALPHABET = 26;

  const size_t text_len = strlen(text);
  const char *end = text + text_len;

  const char big_a = 'A';
  const char small_a = 'a';

  const char modulo_inverse = find_modulo_inverse(multiplier, LETTERS_IN_ALPHABET, 1000);
  if (modulo_inverse < 0)
    return;

  for (char *it = text; it != end; ++it)
  {
    const char &base = *it >= small_a ? small_a : big_a;
    int letter_idx = *it - base;
    int new_letter_idx = ((letter_idx - shift) * modulo_inverse) % LETTERS_IN_ALPHABET;
    new_letter_idx = (new_letter_idx + LETTERS_IN_ALPHABET) % LETTERS_IN_ALPHABET;
    if (new_letter_idx < 0)
      break;

    *it = new_letter_idx + base;
  }
}

int main()
{
  char text[] = "RGMRQERQMZMZXMDENNZUQFD";
  const char coprimes_to_26[] = {3, 5, 7, 9, 11, 15, 17, 19, 21};

  for (int a : coprimes_to_26)
  {
    for (int b = 0; b < 26; ++b)
    {
      char text_buf[sizeof(text)];
      strcpy(text_buf, text);
      affine_decryption(text_buf, a, b);
      printf("%2d-%2d: %s\n", a, b, text_buf);
    }
  }
}