#include <iostream>
#include <string>

std::string replace_all_occurences(std::string source, char c, std::string replacement)
{
  size_t pos = source.find(c);
  while (pos != std::string::npos)
  {
    source.replace(pos, 1, replacement);
    pos = source.find(c, pos + replacement.length());
  }

  return source;
}

std::string string_to_html(std::string source)
{
  source = replace_all_occurences(source, '&', "&amp;");
  source = replace_all_occurences(source, '<', "&lt;");
  source = replace_all_occurences(source, '>', "&gt;");
  return source;
}

bool test_conversion(std::string source, std::string expected)
{
  std::string result;
  result = string_to_html(source);
  return result.compare(expected) == 0;
}

typedef struct test_sample
{
  const std::string input;
  const std::string expected;
} test_sample;

int main()
{
  const test_sample samples[] = {
      {"Buns&Bozinos", "Buns&amp;Bozinos"},
      {"1<2", "1&lt;2"},
      {"cake>vegetables", "cake&gt;vegetables"}};

  for (int i = 0; i < sizeof(samples) / sizeof(test_sample); ++i)
  {
    bool result = test_conversion(
        samples[i].input,
        samples[i].expected);

    printf("Test %d: %s {\"%s\" -> \"%s\"}\n",
           i,
           result ? "success" : "FAIL",
           samples[i].input.c_str(),
           samples[i].expected.c_str());
  }

  return 0;
}