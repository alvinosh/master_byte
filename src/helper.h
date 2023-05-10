#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

#define UNUSED(x) (void)(x)

typedef enum
{
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    Reset
} Colors;

int helper_get_int(int *num);
int helper_get_string(char *line);
void helper_prompt(char *message);

void helper_bg_color(Colors color);
void helper_fg_color(Colors color);

#endif