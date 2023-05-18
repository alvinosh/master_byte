#include "customer.h"

static const char *const customer_option_desc[Customer_Option_Count] = {
    "Search Flights",
    "Search Flight By From Airport",
    "Book Flight",
    "My Bookings",
    "Quit",
};

void customer_search_flights(System *system)
{
    int *flightCount=malloc(sizeof(int));
    Flight *flights=malloc(sizeof(Flight)*BUFSIZ);
    
    system_flight_get_all(system, flights, flightCount);

    for (int i = 0; i < *flightCount; i++)
    {
        if (flights[i].entity.is_deleted == false) {
            system_flight_print_one(&flights[i]);
        }
    }

}

void customer_book_flight(System *system)
{
    Booking *booking = malloc(sizeof(Booking));

    helper_prompt("Enter The Flight ID You Want To Book");
    int *flight_id = malloc(sizeof(int));
    if (helper_get_int(flight_id) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return;
    }
    booking->flight_id = *flight_id;

    helper_prompt("Enter The First Name");
    char *first_name = malloc(sizeof(char) * BUFSIZ);
    if (helper_get_string(first_name) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return;
    }
    strcpy(booking->first_name, first_name);

    helper_prompt("Enter The Last Name");
    char *last_name = malloc(sizeof(char) * BUFSIZ);
    if (helper_get_string(last_name) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return;
    }
    strcpy(booking->last_name, last_name);


    system_booking_add(system, booking);

}

void customer_get_flight_by_from_airport(System *system)
{
    helper_prompt("Enter The Airport You Want Flights From");
    printf("\n");
    char *from_air = malloc(sizeof(char) * BUFSIZ);
    if (helper_get_string(from_air) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return;
    }

    Flight flights[BUFSIZ];
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
void customer_my_bookings(System *system)
{
    helper_prompt("Enter The First Name");
    char *first_name = malloc(sizeof(char) * BUFSIZ);
    if (helper_get_string(first_name) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return;
    }

    helper_prompt("Enter The Last Name");
    char *last_name = malloc(sizeof(char) * BUFSIZ);
    if (helper_get_string(last_name) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return;
    }

    Booking bookings[BUFSIZ];
    int booking_count = 0;
    system_booking_get_all(system, bookings, &booking_count);

    for (int i = 0; i < booking_count; i++)
    {

         if (strcmp(first_name, bookings[i].first_name) == 0 && strcmp(last_name, bookings[i].last_name) == 0)
        {
            system_booking_print_one(&bookings[i]);
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
            customer_search_flights(system);
            break;
        case Customer_Book_Flight:
            customer_book_flight(system);
            break;
        case Customer_Flights_By_From_Airport:
            customer_get_flight_by_from_airport(system);
            break;
        case Customer_My_Bookings:
            customer_my_bookings(system);
            break;
        case Customer_Quit:
            loop = 0;
            break;
        case Customer_Option_Count:
            break;
        }
    }
}
