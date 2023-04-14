#include "customer.h"

static const char *const customer_option_desc[Customer_Option_Count] = {
    "Search Flights",
    "Book Flight",
    "Quit",
};

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

void customer_search_flights()
{
    helper_prompt("From");
    char from[256];
    if (fgets(from, sizeof from, stdin) != NULL)
    {
        from[strlen(from) - 1] = '\0';
    }
    helper_prompt("To");
    char to[256];
    if (fgets(to, sizeof to, stdin) != NULL)
    {
        to[strlen(to) - 1] = '\0';
    }
    helper_prompt("Date");
    char date[256];
    if (fgets(date, sizeof date, stdin) != NULL)
    {
        date[strlen(date) - 1] = '\0';
    }
    helper_prompt("Time");
    char time[256];
    if (fgets(time, sizeof time, stdin) != NULL)
    {
        time[strlen(time) - 1] = '\0';
    }
    helper_prompt("Seats");
    char seats[256];
    if (fgets(seats, sizeof seats, stdin) != NULL)
    {
        seats[strlen(seats) - 1] = '\0';
    }
    helper_prompt("Class");
    char class[256];
    if (fgets(class, sizeof class, stdin) != NULL)
    {
        class[strlen(class) - 1] = '\0';
    }
    printf("Searching Flights \n");
    printf("From: %s \n", from);
    printf("To: %s \n", to);
    printf("Date: %s \n", date);
    printf("Time: %s \n", time);
    printf("Seats: %s \n", seats);
    printf("Class: %s \n", class);
}

void customer_book_flight()
{
    printf("UNIMPLEMENTED \n");
}