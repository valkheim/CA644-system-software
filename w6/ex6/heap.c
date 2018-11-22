#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   int pid = getpid();
   printf("PID = %d\n", pid);
   int size = 1;

   while(1)
   {
      // Allocate some memory
      printf("How much to malloc: "); // how much?
      scanf("%d", &size);
      //  so much!
      char *ptr = malloc(size);
      printf("ptr = %p (%d)\n", ptr, size);
      // Note memory not freed!
      // Memory leak! This is a naughty program.
   }
}
