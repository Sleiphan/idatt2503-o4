#include <stdio.h>
#include <string.h>

void ceasar_shift(char *string, const int shift)
{
  static const int LETTERS_IN_ALPHABET = 26;

  const size_t text_len = strlen(string);
  const char *end = string + text_len;

  const char big_a = 'A';
  const char small_a = 'a';

  for (char *it = string; it != end; ++it)
  {
    const char &base = *it >= small_a ? small_a : big_a;
    char letter_idx = *it - base;
    char new_letter_idx = (letter_idx + shift) % LETTERS_IN_ALPHABET;
    *it = new_letter_idx + base;
  }
}

int main()
{
  const char cipher[] = "SEQSX QYHFEHJ CYDKJU IESA";

  for (int i = 1; i < 26; ++i)
  {
    char buf[sizeof(cipher)];
    strcpy(buf, cipher);
    ceasar_shift(buf, i);
    printf("%d: %s\n", i, buf);
  }

  return 0;
}