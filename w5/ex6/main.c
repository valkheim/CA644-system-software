#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define READ_SIZE (1024L)

static int my_exit(char * const * const);
static int my_cd(char * const * const);

static char *builtin_slug[] = {
  "exit",
  "cd"
};

static int (*builtin_func[]) (char * const * const) = {
  &my_exit,
  &my_cd
};

static int my_exit(char * const * const __attribute__((unused))args)
{
  return 0;
}

static int my_cd(char * const * const args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("Shell Error:");
    }
  }
  return 1;
}

static int launch(char * const * const args)
{
  pid_t wpid;

  int status;
  pid_t const pid = fork();

  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      perror("Shell Error:");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("Shell Error:");
  } else {
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  return 1;
}

static int execute(char * const * const args)
{
  unsigned int i;

  for (i = 0; i < sizeof(builtin_slug) / sizeof(builtin_slug[0]); i++) {
    if (strcmp(args[0], builtin_slug[i]) == 0)
      return (*builtin_func[i])(args);
  }
  return launch(args);
}

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

static char *get_next_line(int const fd)
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

static char **splittab(char *s, char const tkn)
{
  unsigned int i, x, y;
  char **t;
  i = y = 0;
  if ((t = malloc(sizeof(char*) * (strlen(s) + 1))) == NULL) return (NULL);
  while (i < strlen(s))
  {
    while (s[i] == tkn) i++;
    if ((t[y] = malloc(sizeof(char) * (strlen(s) + 1))) == NULL) return (NULL);
    x = 0;
    while (s[i] != tkn && s[i] != 0) t[y][x++] = s[i++];
    t[y++][x] = '\0';
  }
  t[y] = NULL;
  return (t);
}

static void free_args(char * const *args)
{
  while (*args) free(*args++);
}

int main()
{
  char *line;
  char **args;
  int status;

  do {
    write(1, "> ", 2);
    line = get_next_line(STDIN_FILENO);
    if (line) {
      args = splittab(line, ' ');
      status = execute(args);
      free(line);
      free_args(args);
      free(args);
    } else {
      exit(0);
    }
  } while (status);
}
