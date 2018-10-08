/*
~/system_software/w2 > locale
LANG=fr_FR.UTF-8
LC_CTYPE="fr_FR.UTF-8"
LC_NUMERIC="fr_FR.UTF-8"
LC_TIME="fr_FR.UTF-8"
LC_COLLATE=fr_FR.UTF-8
LC_MONETARY="fr_FR.UTF-8"
LC_MESSAGES=
LC_PAPER="fr_FR.UTF-8"
LC_NAME="fr_FR.UTF-8"
LC_ADDRESS="fr_FR.UTF-8"
LC_TELEPHONE="fr_FR.UTF-8"
LC_MEASUREMENT="fr_FR.UTF-8"
LC_IDENTIFICATION="fr_FR.UTF-8"
LC_ALL=
~/system_software/w2 > printf "ok" | xxd
00000000: 6f6b                                     ok
~/system_software/w2 > printf "ok" | iconv -f UTF-8 -t UTF-16LE  | xxd
00000000: 6f00 6b00                                o.k.
~/system_software/w2 > printf "ok" | iconv -f UTF-8 -t UTF-16BE  | xxd
00000000: 006f 006b                                .o.k
~/system_software/w2 > clang -Weverything ex4.c && printf "ok" | iconv -f UTF-8 -t UTF-16LE | ./a.out | xxd
00000000: 006f 006b                                .o.k
~/system_software/w2 > echo "ı" | iconv -f UTF-8 -t UTF-16LE | xxd
00000000: 3101 0a00                                1...
~/system_software/w2 > echo "ı" | iconv -f UTF-8 -t UTF-16LE | ./a.out | xxd
00000000: 0131 000a                                .1..
*/

#include <unistd.h>
#include <stdint.h>
#include <err.h>

#define READ_SIZE (1024L)

int main()
{
  uint8_t buffer[READ_SIZE];
  ssize_t nread;

  /* We assume input is less than READ_SIZE bytes and BOM is not given */
  if ((nread = read(0, buffer, READ_SIZE)) == -1)
    errx(1, "Cannot read user input");
  /* We assume that there will be an even number of bytes in the input */
  for (ssize_t i = 0 ; i < nread ; i += 2)
  {
    write(1, buffer+i+1, 1);
    write(1, buffer+i, 1);
  }
  return 0;
}
