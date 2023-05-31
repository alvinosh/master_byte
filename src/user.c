#include "user.h"
#include "helper.h"

User_Type user_type_get()
{
    helper_prompt("");
    int *c = malloc(sizeof(int));
    if (helper_get_int(c) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return user_type_get();
    }
    if (*c - 1 >= 0 && *c - 1 < User_Type_Count)
    {
        return *c - 1;
    }
    else
    {
        printf("Invalid Option. Please Try Again \n");
        return user_type_get();
    }
}

void user_greet()
{
    helper_bg_color(Blue);
    helper_fg_color(White);
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("*                                                             *\n");
    printf("*     Welcome To The BLACK HATS Flight Rservations System.    *\n");
    printf("*     Please Enter Your User Type.                            *\n");
    printf("*         1. Administrator                                    *\n");
    printf("*         2. Customer                                         *\n");
    printf("*                                                             *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
    helper_bg_color(Reset);
    helper_fg_color(Reset);
    printf("\n");
}
