#include <openssl/evp.h>
#include <string.h>

int increment_string(unsigned char *string, const size_t buffer_size, const char LETTER_MIN, const char LETTER_MAX)
{
  size_t string_length = strlen(string);
  size_t pos = string_length - 1;

  if (pos == (size_t)0 - 1)
  {
    string[0] = LETTER_MIN;
    pos = 0;
  }
  else
    string[pos] += 1;

  while (pos > 0 & string[pos] > LETTER_MAX)
  {
    string[pos] = LETTER_MIN;
    --pos;
    string[pos] += 1;
  }

  // Do we need to increase the length of the string?
  if (string[0] > LETTER_MAX)
  {
    if (string_length + 1 >= buffer_size)
      return 1; // Exit if we cannot safely increase the length of the string.

    memset(string, LETTER_MIN, string_length + 1);
    string_length += 1;
    string[string_length] = '\0';
  }

  return 0;
}

void buf_to_hex(unsigned char *digest, size_t length, char *hex_output)
{
  static const char hex_digits[] = "0123456789abcdef";
  for (size_t i = 0; i < length; i++)
  {
    hex_output[i * 2] = hex_digits[(digest[i] >> 4) & 0xF];
    hex_output[i * 2 + 1] = hex_digits[digest[i] & 0xF];
  }
  hex_output[length * 2] = '\0'; // Null-terminate the string
}

int main()
{
  static const char PASSWORD_HASH[] = "ab29d7b5c589e18b52261ecba1d3a7e7cbf212c6";
  static const char SALT[] = "Saltet til Ola";

  static const unsigned char LETTERS_MIN = 65;
  static const unsigned char LETTERS_MAX = 122;

  static const int MAX_PASSWORD_LEN = 5;
  static const int NUM_ITERATIONS = 2048;

  char current_password[MAX_PASSWORD_LEN + 1]; // +1 to include the terminating character
  unsigned char current_hash[sizeof(PASSWORD_HASH) / 2 + 1];
  char current_hash_hex[sizeof(PASSWORD_HASH)];
  int not_found = 1;
  int iteration = 0;

  memset(current_password, 0, sizeof(current_password));
  memset(current_hash, 0, sizeof(current_hash));
  memset(current_hash_hex, 0, sizeof(current_hash_hex));

  while (not_found && !increment_string(current_password, MAX_PASSWORD_LEN + 1, LETTERS_MIN, LETTERS_MAX))
  {
    int err = PKCS5_PBKDF2_HMAC_SHA1(
        current_password,         // password
        strlen(current_password), // password length
        SALT,                     // salt
        strlen(SALT),             // salt length
        NUM_ITERATIONS,           // number of iterations
        sizeof(current_hash) - 1, // derived key length
        current_hash              // output hash buffer
    );

    buf_to_hex(current_hash, sizeof(current_hash) - 1, current_hash_hex);

    not_found = strcmp(current_hash_hex, PASSWORD_HASH);

    if (iteration % 999 == 0)
      printf("%s\n", current_password);

    ++iteration;
  }

  if (!not_found)
    printf("Password found!: %s\n", current_password);
  else
    printf("No password found\n");

  return 0;
}