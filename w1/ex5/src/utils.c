#include "ex5.h"

/* checks if s is a valid number */
int parseNumber(char const *s)
{
  while (*s)
  {
    if (*s > '9' || *s < '0')
    {
      if (*s != '+' && *s != '-')
        return -1;
    }
    s++;
  }
  return 0;
}

/* char * number to int */
int getnbr(char const * const s)
{
  size_t i;
  int n;
  int sign;

  n = 0;
  i = 0;
  sign = 1;
  while (s[i] != 0 && (s[i] == '+' || s[i] == '-'))
    if (s[i++] == '-')
      sign = -sign;
  while (s[i])
    n = n * 10 + s[i++] - 48;
  return sign * n;
}

/* write n on stdout */
void putnbr(int n)
{
  if (n < 0)
  {
    putchar('-');
    n *= -1;
  }
  if (n >= 10)
    putnbr(n / 10);
  putchar(n % 10 + '0');
}
