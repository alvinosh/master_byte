#include "customer.h"

Customer_Option customer_option_get()
{
    helper_prompt("");
    char c = helper_get_int();
    if (c == -1)
    {
        printf("Invalid Option. Please Try Again \n");
        return customer_option_get();
    }
    switch (c)
    {
    case 1:
        return Search_Flights;
    case 2:
        return Book_Flight;
    case 3:
        return Customer_Quit;
    default:
        printf("Invalid Option. Please Try Again \n");
        return customer_option_get();
    }
}

void customer_option_help()
{
    printf("Please Enter Your Option. \n");
    printf("    1. Search Flights \n");
    printf("    2. Book Flight \n");
    printf("    3. Quit \n");
}

void customer_run()
{
    customer_option_help();
    while (1)
    {
        Customer_Option option = customer_option_get();
        switch (option)
        {
        case Search_Flights:
            printf("Search Flights \n");
            break;
        case Book_Flight:
            printf("Book Flight \n");
            break;
        case Customer_Quit:
            printf("Quit \n");
            return;
        case Customer_Option_Count:
            break;
        }
    }
}
