#include "ex5.h"

static void printNegativeSum(int const n)
{
  int i;
  int res;

  i = n;
  res = 0;
  while (i <= 1)
    res += i++;
  putnbr(res);
}

static void printPositiveSum(int const n)
{
  int i;
  int res;

  i = 1;
  res = 0;
  while (i <= n)
    res += i++;
  putnbr(res);
}

int main()
{
  char *s;
  int n;

  if ((s = get_next_line(0)) == NULL)
    errx(1, "Cannot read user input");
  if (parseNumber(s) == -1)
    errx(1, "Invalid number");
  n = getnbr(s);
  if (n > 0)
    printPositiveSum(n);
  else
    printNegativeSum(n);
}
