#include "ex5.h"

/*
 * input : -3
 * computation : -3+-2+-1+-0+1
 * result : -5
*/
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

/*
 * input : 3
 * computation : 0+1+2+3
 * result : 6
*/
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

  /* read user input */
  if ((s = get_next_line(STDIN_FILENO)) == NULL)
    errx(1, "Cannot read user input");
  /* parse user input */
  if (parseNumber(s) == -1)
    errx(1, "Invalid number");
  /* retrieve user input as an int */
  n = getnbr(s);
  /* compute the sum */
  if (n > 0)
    printPositiveSum(n);
  else
    printNegativeSum(n);
  return 0;
}
