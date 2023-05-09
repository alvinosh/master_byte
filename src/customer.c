#include "customer.h"

static const char *const customer_option_desc[Customer_Option_Count] = {
    "Search Flights",
    "Book Flight",
    "Book Flight By From Airport",
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

void customer_get_flight_by_from_airport(System *system)
{
    helper_prompt("Enter The Airport You Want Flights From");
    char *from_air = malloc(sizeof(char) * BUFSIZ);
    if (helper_get_string(from_air) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return;
    }

    Flight flights[1024];
    int flight_count = 0;
    system_flight_get_all(system, flights, &flight_count);

    for (int i = 0; i < flight_count; i++)
    {
        if (strcmp(from_air, flights[i].from_airport) == 0)
        {
            // printf("%s ", flights[i].price);
            system_flight_print_one(&flights[i]);
        }
    }
}

Customer_Option customer_option_get()
{
    helper_prompt("");
    int *c = malloc(sizeof(int));
    if (helper_get_int(c) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return customer_option_get();
    }

    if (*c - 1 >= 0 && *c - 1 < Customer_Option_Count)
    {
        return *c - 1;
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

void customer_run(System *system)
{
    customer_option_help();
    int loop = 1;
    while (loop)
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
        case Customer_Flights_By_From_Airport:
            customer_get_flight_by_from_airport(system);
            break;
        case Customer_Quit:
            loop = 0;
            break;
        case Customer_Option_Count:
            break;
        }
    }
}
