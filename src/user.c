#include "user.h"

User_Type user_type_get()
{
    helper_prompt("");
    int c = helper_get_int();
    if (c == -1)
    {
        printf("Invalid Option. Please Try Again \n");
        return user_type_get();
    }
    if (c - 1 >= 0 && c - 1 < User_Type_Count)
    {
        return c - 1;
    }
    else
    {
        printf("Invalid Option. Please Try Again \n");
        return user_type_get();
    }
}

void user_greet()
{
    printf("Welcome To The Master Byte Flight Rservations System. \n");
    printf("Please Enter Your User Type. \n");
    printf("    1. Administrator \n");
    printf("    2. Customer \n");
}
