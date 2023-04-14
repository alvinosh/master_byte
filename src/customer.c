#include "customer.h"

static const char *const customer_option_desc[Customer_Option_Count] = {
    "Search Flights",
    "Book Flight",
    "Quit",
};

void customer_search_flights()
{
    printf("UNIMPLEMENTED \n");
}

void customer_book_flight()
{
    printf("UNIMPLEMENTED \n");
}

Customer_Option customer_option_get()
{
    helper_prompt("");
    char c = helper_get_int();
    if (c == -1)
    {
        printf("Invalid Option. Please Try Again \n");
        return customer_option_get();
    }
    if (c - 1 >= 0 && c - 1 < Customer_Option_Count)
    {
        return c - 1;
    }
    else
    {
        printf("Invalid Option. Please Try Again \n");
        return customer_option_get();
    }
}

void customer_option_help()
{
    printf("Please Enter Your Option. \n");
    for (int i = 0; i < Customer_Option_Count; i++)
    {
        printf("    %d. %s \n", i + 1, customer_option_desc[i]);
    }
}

void customer_run()
{
    customer_option_help();
    while (1)
    {
        Customer_Option option = customer_option_get();
        switch (option)
        {
        case Customer_Search_Flights:
            customer_search_flights();
            break;
        case Customer_Book_Flight:
            customer_book_flight();
            break;
        case Customer_Quit:
            printf("Quit \n");
            return;
        case Customer_Option_Count:
            break;
        }
    }
}
