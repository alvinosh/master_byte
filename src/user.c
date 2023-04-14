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
    switch (c)
    {
    case 1:
        return Administrator;
    case 2:
        return Customer;
    default:
        printf("Invalid Option. Please Try Again \n");
        return user_type_get();
    }
}
