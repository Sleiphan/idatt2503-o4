#include "print_filter_c_fuzz.h"
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
    const char *symbol = 0;

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
