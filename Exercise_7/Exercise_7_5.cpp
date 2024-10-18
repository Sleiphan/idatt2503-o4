#include <stdio.h>
#include <string.h>

void create_dictionary(char dictionary[256])
{
  for (int i = 0; i < 256; ++i)
    dictionary[i] = i;
}

void set_dict_to_solution(char dictionary[256])
{
  dictionary['D'] = ' '; // #
  dictionary['I'] = 'e'; // #
  dictionary[' '] = 't'; // #
  dictionary['B'] = 'n'; // #
  dictionary['C'] = 'o'; // #
  dictionary['V'] = 's'; // #
  dictionary['Q'] = 'i'; // #
  dictionary['W'] = 'r'; // #
  dictionary['T'] = 'h'; // #
  dictionary['S'] = 'u'; // #
  dictionary['E'] = 'c'; // #
  dictionary['M'] = 'b'; // #
  dictionary['O'] = 'l'; // #
  dictionary['J'] = 'd'; // #
  dictionary['A'] = 'g'; // #
  dictionary['F'] = 'k'; // #
  dictionary['K'] = 'a'; // #
  dictionary['Y'] = 'y'; // #
  dictionary['P'] = 'p'; // #
  dictionary['H'] = 'f'; // #
  dictionary['X'] = 'q'; // #
  dictionary['R'] = 'w'; // #
  dictionary['G'] = 'x'; // #
  dictionary['Z'] = 'z'; // #
  dictionary['U'] = 'm'; // #
  dictionary['N'] = 'j'; // #
  dictionary['L'] = 'v'; // #
}

void string_substitute(char *dst, const char *src, char dictionary[256])
{
  const char *end = src + strlen(src);
  const char *it_src = src;
  char *it_dst = dst;

  for (; it_src != end; ++it_src, ++it_dst)
    *it_dst = dictionary[*it_src];
}

int main()
{
  const char ENCRYPTED_STRING[] = "UCBCKOPTKMI QEDVSMV Q S QCBDEKBDQBDAIBIWKODIKVQOYDMIDMWCFIBDSVQBADHWIXSIBEYDKBKOYVQVD TQVDCBOYDRCWFVDRIOODQHD TIDPOKQB IG DQVDOCBADIBCSATDKBJDQVDBC D CCDJQHHIWIB DHWCUDBCWUKOD IG DCBIDVTCSOJDKOVCDFBCRDRTK DOKBASKAID TIDPOKQB IG DQVDRWQ  IBDQBDKVD TIDHWIXSIBEQIVDCHDOI  IWVDLKWYDHWCUDOKBASKAID CDOKBASKAIDVCUID IG VDKWIDTKWJIWD CDMWIKFD TKBDC TIWVDKBDIGKUPOIDQVD TIDVIB IBEID TIDXSQEFDMWCRBDHCGDNSUPVDCLIWD TIDOKZYDJCAD TQVDVIB IBEIDECB KQBVDILIWYDOI  IWDCHD TIDKOPTKMI DBC DTIOPQBAD TIDEWYP KBKOYV DACCJDOSEF";
  char decrypted_string[sizeof(ENCRYPTED_STRING)];

  char dictionary[256];
  create_dictionary(dictionary);
  set_dict_to_solution(dictionary);

  string_substitute(decrypted_string, ENCRYPTED_STRING, dictionary);

  printf("%s\n\n", decrypted_string);

  return 0;
}