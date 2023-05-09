#include "helper.h"

int helper_get_int(int *num)
{
    int a = scanf("%d", num);
    if (a == 0)
    {
        fprintf(stderr, "Error: failed to read input\n");
        return -1;
    }
    else if (a == EOF)
    {
        fprintf(stderr, "Error: failed to read input\n");
        return -1;
    }
    else if (a == 1)
    {
        return 0;
    }
    else
    {
        fprintf(stderr, "Error: failed to read input\n");
        return -1;
    }

    return 0;
}

int helper_get_string(char *line)
{

    int a = scanf("%s", line);
    // error handling
    if (a == 0)
    {
        fprintf(stderr, "Error: failed to read input\n");
        return -1;
    }
    else if (a == EOF)
    {
        fprintf(stderr, "Error: failed to read input\n");
        return -1;
    }
    else if (a == 1)
    {
        return 0;
    }
    else
    {
        fprintf(stderr, "Error: failed to read input\n");
        return -1;
    }
}

void helper_prompt(char *message)
{
    printf("%s > ", message);
}