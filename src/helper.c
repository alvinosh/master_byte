#include "helper.h"

void helper_get_int(int *num)
{
    char buffer[1024];
    helper_get_string(buffer);
    if (buffer == NULL)
    {
        num = NULL;
        return;
    }

    char *endptr;
    errno = 0;
    int n = strtol(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer || *endptr != '\n' || n <= 0 || n > INT_MAX)
    {
        num = NULL;
        return;
    }

    *num = (int)num;
}

void helper_get_string(char *line)
{
    if (fgets(line, sizeof line, stdin) != NULL)
    {
        line[strlen(line) - 1] = '\0';
    }
    else
    {
        line = NULL;
    }
}
