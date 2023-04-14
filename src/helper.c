#include "pch.h"

int helper_get_int()
{
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return -1;
    }
    char *endptr;
    errno = 0;
    long num = strtol(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer || *endptr != '\n' || num <= 0 || num > INT_MAX)
    {
        return -1;
    }
    return (int)num;
}

char *helper_get_string()
{
    char line[1024];
    if (fgets(line, sizeof line, stdin) != NULL)
    {
        line[strlen(line) - 1] = '\0';
        return line;
    }
    else
    {
        return -1;
    }
}

void helper_prompt(char *message)
{
    printf("%s > ", message);
}