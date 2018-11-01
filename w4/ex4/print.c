#include <stdio.h>
#include "ex1.h"

int main() {
  for (int i = 0.0 ; i < 10 ; i++)
    printf("%d squared is %.f\n", i, arithmetic(i));
}
