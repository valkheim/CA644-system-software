#pragma once

#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <err.h>

int getnbr(char const * const s);
void putnbr(int n);
int parseNumber(char const *s);
char *get_next_line(int const fd);
