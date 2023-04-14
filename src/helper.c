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

void helper_greet()
{
    printf("Welcome To The Master Byte Flight Rservations System. \n");
    printf("Please Enter Your User Type. \n");
    printf("    1. Administrator \n");
    printf("    2. Customer \n");
}

void helper_prompt(char *message)
{
    printf("%s > ", message);
}