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

void helper_bg_color(Colors color)
{
    switch (color)
    {
    case Red:
        printf("\033[41m");
        break;
    case Green:
        printf("\033[42m");
        break;
    case Yellow:
        printf("\033[43m");
        break;
    case Blue:
        printf("\033[44m");
        break;
    case Magenta:
        printf("\033[45m");
        break;
    case Cyan:
        printf("\033[46m");
        break;
    case White:
        printf("\033[47m");
        break;
    case Reset:
        printf("\033[0m");
        break;
    default:
        printf("\033[0m");
        break;
    }
}

void helper_fg_color(Colors color)
{
    switch (color)
    {
    case Red:
        printf("\033[31m");
        break;
    case Green:
        printf("\033[32m");
        break;
    case Yellow:
        printf("\033[33m");
        break;
    case Blue:
        printf("\033[34m");
        break;
    case Magenta:
        printf("\033[35m");
        break;
    case Cyan:
        printf("\033[36m");
        break;
    case White:
        printf("\033[37m");
        break;
    case Reset:
        printf("\033[0m");
        break;
    default:
        printf("\033[0m");
        break;
    }
}