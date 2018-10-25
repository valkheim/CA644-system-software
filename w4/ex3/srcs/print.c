#include <stdio.h>
#include <libarithmetic/arithmetic.h>

int main() {
  for (int i = 0.0 ; i < 10 ; i++)
    printf("%d squared is %.f\n", i, arithmetic(i));
}
