#include "ex5.h"

#define READ_SIZE (1024L)

static int check_bn(char const * const s)
{
  int i;

  i = 0;
  while (i < READ_SIZE)
  {
    if (s[i] == '\n')
      return i;
    i++;
  }
  return -1;
}

static char *shift(char const * const buf, char const * const buffer,
    int const ncpy, int const size)
{
  char *dest;
  int i;
  int k;
  size_t len;

  i = 0;
  k = 0;
  len = 0;
  if (buf != NULL && buffer != NULL)
    len = strlen(buf) + strlen(buffer);
  if ((dest = malloc(sizeof(*dest) * (len + READ_SIZE + 1))) == NULL)
    return (NULL);
  if (buf != NULL)
    while (buf[i])
      dest[k++] = buf[i++];
  i = ncpy;
  while (i < size)
    dest[k++] = buffer[i++];
  dest[k] = '\0';
  return (dest);
}

/* read on fd */
char *get_next_line(int const fd)
{
  static char buffer[READ_SIZE];
  static ssize_t nread;
  static int ncpy;
  char *buf;

  nread = READ_SIZE;
  ncpy = -READ_SIZE;
  buf = NULL;
  if (nread <= 0)
    return (NULL);
  if (ncpy > -READ_SIZE)
    buf = shift(buf, buffer, (ncpy + 1), READ_SIZE);
  while ((nread = read(fd, buffer, READ_SIZE)) > 0)
  {
    buffer[nread] = '\0';
    if (check_bn(buffer) == -1)
      buf = shift(buf, buffer, 0, READ_SIZE);
    else
    {
      ncpy = check_bn(buffer);
      buf = shift(buf, buffer, 0, ncpy);
      return (buf);
    }
  }
  return (buf);
}
