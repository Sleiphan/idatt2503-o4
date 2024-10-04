#include "print_filter_c_fuzz.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  size_t buffer_size = size * 2;
  char *str = (char *)malloc(sizeof(char) * buffer_size);
  memcpy(str, data, size);
  str[size] = '\0';

  string_to_html(str, size + 1, buffer_size);

  free(str);

  return 0;
}
