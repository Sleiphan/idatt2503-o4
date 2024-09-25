#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief Formats text to a string usable in html syntax.
/// Currently only converts these reserved characters to their correct html-phrase: '&', '<', and '>'.
/// @param buffer The char buffer containing the input string, and receiving the output string.
/// @param source_size The length of the input string, in chars.
/// @param buffer_size The maximal size of 'buffer', in bytes.
/// @return The number of bytes written to 'buffer'.
int string_to_html(char *buffer, const size_t source_size, const size_t buffer_size)
{
  static const char t_amp[] = "&amp;";
  static const char t_lst[] = "&lt;";
  static const char t_grt[] = "&gt;";

  char *tmp_buf = (char *)malloc(buffer_size);

  const char *end_str = buffer + (source_size - 1);
  const char *end_buf = tmp_buf + (buffer_size - 1);

  char *it_s = buffer;
  char *it_d = tmp_buf;

  while (it_s < end_str & it_d < end_buf)
  {
    char symbol_length = 0;
    char *symbol = 0;

    switch (*it_s)
    {
    case '&':
      symbol = t_amp;
      symbol_length = sizeof(t_amp) - 1;
      break;
    case '<':
      symbol = t_lst;
      symbol_length = sizeof(t_lst) - 1;
      break;
    case '>':
      symbol = t_grt;
      symbol_length = sizeof(t_grt) - 1;
      break;
    }

    if (!symbol_length)
    {
      *(it_d++) = *it_s;
    }
    else
    {
      if (symbol_length > end_buf - it_d)
        symbol_length = end_buf - it_d;

      memcpy(it_d, symbol, symbol_length * sizeof(char));
      it_d += symbol_length;
    }

    ++it_s;
  }

  *(it_d++) = '\0';
  strcpy(buffer, tmp_buf);

  const int bytes_written = it_d - tmp_buf;
  free(tmp_buf);
  return bytes_written;
}

int test_convert(const char *source, const char *target, size_t source_element_count, size_t target_element_count)
{
  size_t buffer_size = target_element_count * sizeof(char);
  char *buffer = (char *)malloc(buffer_size);

  memcpy(buffer, source, target_element_count * sizeof(char));
  int new_length = string_to_html(buffer, source_element_count, buffer_size);
  int result = memcmp(buffer, target, target_element_count * sizeof(char));

  free(buffer);
  return result;
}

typedef struct test_sample
{
  const char input[64];
  const char expected[64];
} test_sample;

int main()
{
  const test_sample samples[] = {
      {"Buns&Bozinos", "Buns&amp;Bozinos"},
      {"1<2", "1&lt;2"},
      {"cake>vegetables", "cake&gt;vegetables"},
      {"cake>", "cake&g"}, // Edge case 1
      {"cake>s", "cake&g"} // Edge case 2
  };

  for (int i = 0; i < sizeof(samples) / sizeof(test_sample); ++i)
  {
    int result = test_convert(
        samples[i].input,
        samples[i].expected,
        strlen(samples[i].input) + 1,
        strlen(samples[i].expected) + 1);

    printf("Test %d: %d {\"%s\" -> \"%s\"}\n", i, result, samples[i].input, samples[i].expected);
  }

  return 0;
}