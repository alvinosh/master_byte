#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

#define UNUSED(x) (void)(x)

void helper_get_int(int *num);
void helper_get_string(char *line);
void helper_prompt(char *message);

#endif