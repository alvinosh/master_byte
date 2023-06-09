#include "customer.h"

static const char *const customer_option_desc[Customer_Option_Count] = {
    "Search Flights",
    "Search Flights By cheapest",
    "Search Flight By From Airport",
    "Search Flight By ID",
    "Book Flight",
    "Cancel Booking",
    "My Bookings",
    "Quit",
};

void customer_search_flights(System *system)
{

    LinkedList flights;
    ll_init(&flights);
    system_entity_get_all(system, SYSTEM_FLIGHT, &flights);
    for (Iterator i = iter_create(&flights); i.current != NULL; iter_next(&i))
    {
        Flight *flight = ((Flight *)i.current->data);
        if (flight->entity.is_deleted == false)
        {
            helper_fg_color(Cyan);
            system_flight_print_one(flight);
            helper_fg_color(Reset);
        }
        printf("\n");
    }
}
int system_Flight_Compare_price(void *a, void *b)
{
    Flight *flight_a = (Flight *)a;
    Flight *flight_b = (Flight *)b;

    // convert the flight prices to int and compare them

    int price_a = atoi(flight_a->price);
    int price_b = atoi(flight_b->price);

    return price_a - price_b;
}

void Customer_search_flights_by_cheapest(System *system)
{
    LinkedList flights;
    ll_init(&flights);
    system_entity_get_all(system, SYSTEM_FLIGHT, &flights);
    ll_sort(&flights, system_Flight_Compare_price);

    helper_prompt("Enter How Many Cheap Flights You Want To Get");
    int *cheap_flights = malloc(sizeof(int));
    if (helper_get_int(cheap_flights) != 0)
    {
        helper_fg_color(Red);
        printf("Invalid Option. Please Try Again \n");
        helper_fg_color(Reset);
        return;
    }
    int cnt = 0;

    for (Iterator i = iter_create(&flights); i.current != NULL; iter_next(&i))
    {
        if (cnt == *cheap_flights)
        {
            break;
        }
        Flight *flight = ((Flight *)i.current->data);
        if (flight->entity.is_deleted == false)
        {
            helper_fg_color(Cyan);
            system_flight_print_one(flight);
            helper_fg_color(Reset);
            cnt++;
        }
        printf("\n");
    }
}

void customer_book_flight(System *system)
{
    Booking *booking = malloc(sizeof(Booking));

    helper_prompt("Enter The Flight ID You Want To Book");
    int *flight_id = malloc(sizeof(int));
    if (helper_get_int(flight_id) != 0)
    {
        helper_fg_color(Red);
        printf("Invalid Option. Please Try Again \n");
        helper_fg_color(Reset);
        return;
    }

    LinkedList flights;
    ll_init(&flights);
    system_entity_get_all(system, SYSTEM_FLIGHT, &flights);
    for (Iterator i = iter_create(&flights); i.current != NULL; iter_next(&i))
    {
        Flight *flight = ((Flight *)i.current->data);

        if (*flight_id == flight->entity.id)
        {
            booking->flight_id = *flight_id;

            helper_prompt("Enter The First Name");
            char *first_name = malloc(sizeof(char) * BUFSIZ);
            if (helper_get_string(first_name) != 0)
            {
                helper_fg_color(Red);
                printf("Invalid Option. Please Try Again \n");
                helper_fg_color(Reset);
                return;
            }
            strcpy(booking->first_name, first_name);

            helper_prompt("Enter The Last Name");
            char *last_name = malloc(sizeof(char) * BUFSIZ);
            if (helper_get_string(last_name) != 0)
            {
                helper_fg_color(Red);
                printf("Invalid Option. Please Try Again \n");
                helper_fg_color(Reset);
                return;
            }
            strcpy(booking->last_name, last_name);

            system_booking_add(system, booking);
            helper_fg_color(Green);
            printf("Flight Booked \n");
            helper_fg_color(Reset);
            return;
        }
    }
    helper_fg_color(Red);
    printf("Invalid ID. Please Try Again \n");
    helper_fg_color(Reset);
    return;
}
void customer_cancel_booking(System *system)
{
    helper_prompt("Enter The Booking ID You Want To Cancel");
    int *booking_id = malloc(sizeof(int));
    if (helper_get_int(booking_id) != 0)
    {
        helper_fg_color(Red);
        printf("Invalid Option. Please Try Again \n");
        helper_fg_color(Reset);
        return;
    }
    LinkedList *bookings = malloc(sizeof(LinkedList));
    ll_init(bookings);
    system_entity_get_all(system, SYSTEM_BOOKING, bookings);
    for (Iterator i = iter_create(bookings); i.current != NULL; iter_next(&i))
    {
        Booking *booking = ((Booking *)i.current->data);

        if (*booking_id == booking->entity.id)
        {
            system_entity_remove(system, SYSTEM_BOOKING, *booking_id);
            helper_fg_color(Green);
            printf("Booking Cancelled \n");
            helper_fg_color(Reset);
            return;
        }
    }
    helper_fg_color(Red);
    printf("Invalid ID. Please Try Again \n");
    helper_fg_color(Reset);
    return;
}

void customer_get_flight_by_from_airport(System *system)
{
    helper_prompt("Enter The Airport You Want Flights From");
    printf("\n");
    char *from_air = malloc(sizeof(char) * BUFSIZ);
    if (helper_get_string(from_air) != 0)
    {
        helper_fg_color(Red);
        printf("Invalid Option. Please Try Again \n");
        helper_fg_color(Reset);
        return;
    }

    LinkedList flights;
    ll_init(&flights);
    system_entity_get_all(system, SYSTEM_FLIGHT, &flights);
    for (Iterator i = iter_create(&flights); i.current != NULL; iter_next(&i))
    {
        Flight *flight = ((Flight *)i.current->data);

        if (strcmp(from_air, flight->from_airport) == 0)
        {
            helper_fg_color(Cyan);
            system_flight_print_one(flight);
            helper_fg_color(Reset);
        }
    }
}
void customer_flights_by_ID(System *system)
{
    helper_prompt("Enter The Flight ID");
    printf("\n");
    int *flight_id = malloc(sizeof(int));
    if (helper_get_int(flight_id) != 0)
    {
        helper_fg_color(Red);
        printf("Invalid Option. Please Try Again \n");
        helper_fg_color(Reset);
        return;
    }

    LinkedList flights;
    ll_init(&flights);
    system_entity_get_all(system, SYSTEM_FLIGHT, &flights);
    for (Iterator i = iter_create(&flights); i.current != NULL; iter_next(&i))
    {
        Flight *flight = ((Flight *)i.current->data);

        if (*flight_id == flight->entity.id)
        {
            helper_fg_color(Cyan);
            system_flight_print_one(flight);
            helper_fg_color(Reset);
        }
    }
    printf("\n");
}

void customer_my_bookings(System *system)
{
    helper_prompt("Enter The First Name");
    char *first_name = malloc(sizeof(char) * BUFSIZ);
    if (helper_get_string(first_name) != 0)
    {
        helper_fg_color(Red);
        printf("Invalid Option. Please Try Again \n");
        helper_fg_color(Reset);
        return;
    }

    helper_prompt("Enter The Last Name");
    char *last_name = malloc(sizeof(char) * BUFSIZ);
    if (helper_get_string(last_name) != 0)
    {
        helper_fg_color(Red);
        printf("Invalid Option. Please Try Again \n");
        helper_fg_color(Reset);
        return;
    }

    LinkedList *bookings = malloc(sizeof(LinkedList));
    ll_init(bookings);
    system_entity_get_all(system, SYSTEM_BOOKING, bookings);
    for (Iterator i = iter_create(bookings); i.current != NULL; iter_next(&i))
    {
        Booking *booking = ((Booking *)i.current->data);

        if (strcmp(first_name, booking->first_name) == 0 && strcmp(last_name, booking->last_name) == 0 && !booking->entity.is_deleted)
        {
            system_booking_print_one(booking);
            LinkedList flights;
            ll_init(&flights);
            system_entity_get_all(system, SYSTEM_FLIGHT, &flights);
            for (Iterator i = iter_create(&flights); i.current != NULL; iter_next(&i))
            {
                Flight *flight = ((Flight *)i.current->data);

                if (booking->flight_id == flight->entity.id)
                {
                    system_flight_print_one(flight);
                }
            }
            printf("\n");

            return;
        }
    }
    helper_fg_color(Red);
    printf("No Bookings Found with this name. \n");
    helper_fg_color(Reset);
    return;
}

Customer_Option customer_option_get()
{
    helper_prompt("");
    int *c = malloc(sizeof(int));
    if (helper_get_int(c) != 0)
    {
        helper_fg_color(Red);
        printf("Invalid Option. Please Try Again \n");
        helper_fg_color(Reset);
        return customer_option_get();
    }

    if (*c - 1 >= 0 && *c - 1 < Customer_Option_Count)
    {
        return *c - 1;
    }
    else
    {
        helper_fg_color(Red);
        printf("Invalid Option. Please Try Again \n");
        helper_fg_color(Reset);
        return customer_option_get();
    }
}

void customer_option_help()
{
    printf("Please Enter Your Option. \n");
    for (int i = 0; i < Customer_Option_Count; i++)
    {
        helper_fg_color(Yellow);
        printf("    %d. %s \n", i + 1, customer_option_desc[i]);
        helper_fg_color(Reset);
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
        case Customer_Search_Flights_By_Cheapest:
            Customer_search_flights_by_cheapest(system);
            break;
        case Customer_Flights_By_From_Airport:
            customer_get_flight_by_from_airport(system);
            break;
        case Customer_Flights_By_ID:
            customer_flights_by_ID(system);
            break;
        case Customer_Book_Flight:
            customer_book_flight(system);
            break;
        case Cancel_Booking:
            customer_cancel_booking(system);
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