#include "admin.h"

static const char *const admin_option_desc[Admin_Option_Count] = {
    "Add Flight",
    "Remove Flight",
    "Print Flights",
    "Add Airport",
    "Remove Airport",
    "Print Airports",
    "Quit",
};

void admin_add_flight(System *system)
{
    Flight *flight = malloc(sizeof(Flight));

    helper_prompt("Enter The From Airport");
    char *from_airport = malloc(sizeof(char) * BUFSIZ);
    if (helper_get_string(from_airport) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return;
    }
    strcpy(flight->from_airport, from_airport);

    helper_prompt("Enter The To Airport");
    char *to_airport = malloc(sizeof(char) * BUFSIZ);
    if (helper_get_string(to_airport) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return;
    }
    strcpy(flight->to_airport, to_airport);

    helper_prompt("Enter The Departure Date");
    char *Date = malloc(sizeof(char) * BUFSIZ);
    if (helper_get_string(Date) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return;
    }
    strcpy(flight->date, Date);

    helper_prompt("Enter The Price");
    char *price = malloc(sizeof(char) * BUFSIZ);
    if (helper_get_string(price) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return;
    }
    strcpy(flight->price, price);

    system_flight_add(system, flight);
    printf("Flight Added \n");
}

void admin_remove_flight(System *system)
{
    helper_prompt("Enter The Flight ID You Want To Remove");
    int *flight_id = malloc(sizeof(int));
    if (helper_get_int(flight_id) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return;
    }
    system_flight_remove(system, *flight_id);
    printf("Flight Removed \n");
}

void admin_print_flights(System *system)
{
    Flight flights[1024];
    int flight_count = 0;
    system_flight_get_all(system, flights, &flight_count);
    system_flight_print_all(flights, &flight_count);
    printf("\n");
}

void admin_add_airport(System *system)
{

    Airport *airport = malloc(sizeof(Airport));
    
    char *name = malloc(sizeof(char) * BUFSIZ);
    char *code = malloc(sizeof(char) * BUFSIZ);
    char *country = malloc(sizeof(char) * BUFSIZ);
    char *city = malloc(sizeof(char) * BUFSIZ);
    helper_prompt("Enter Airport Name");
    if (helper_get_string(name) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return;
    }
    helper_prompt("Enter Airport Code");
    if (helper_get_string(code) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return;
    }
    helper_prompt("Enter Airport Country");
    if (helper_get_string(country) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return;
    }
    helper_prompt("Enter Airport City");
    if (helper_get_string(city) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return;
    }
    strcpy(airport->name, name);
    strcpy(airport->code, code);
    strcpy(airport->country, country);
    strcpy(airport->city, city);
    system_airport_add(system, airport);


}

void admin_remove_airport(System *system)
{
    helper_prompt("Enter The Airport ID You Want To Remove");
    int *airport_id = malloc(sizeof(int));
    if (helper_get_int(airport_id) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return;
    }
    system_airport_remove(system, *airport_id);
    printf("Airport Removed \n");
   
}

void admin_print_airports(System *system)
{
    Airport airports[1024];
    int airport_count = 0;
    system_airport_get_all(system, airports, &airport_count);
    system_airport_print_all(airports, &airport_count);
    printf("\n");  


}

Admin_Option admin_option_get()
{
    helper_prompt("");
    int *c = malloc(sizeof(int));

    if (helper_get_int(c) != 0)
    {
        printf("Invalid Option. Please Try Again \n");
        return admin_option_get();
    }

    if (*c - 1 >= 0 && *c - 1 < Admin_Option_Count)
    {
        return *c - 1;
    }
    else
    {
        printf("Invalid Option. Please Try Again \n");
        return admin_option_get();
    }
}

void admin_option_help()
{

    printf("Please Enter Your Option. \n");
    for (int i = 0; i < Admin_Option_Count; i++)
    {
        printf("    %d. %s \n", i + 1, admin_option_desc[i]);
    }
    printf("\n");
}

void admin_authenticate()
{
    helper_prompt("Password");
    char line[256];

    if (helper_get_string(line) != 0)
    {
        printf("Invalid Password. Please Try Again \n");
        admin_authenticate();
    }
    else
    {
        if (strcmp(line, "admin") == 0)
        {
            printf("Welcome Admin \n");
        }
        else
        {
            printf("Invalid Password. Please Try Again \n");
            admin_authenticate();
        }
    }
}

void admin_run(System *system)
{
    admin_authenticate();
    admin_option_help();
    int loop = 1;
    while (loop)
    {
        Admin_Option option = admin_option_get();
        switch (option)
        {
        case Admin_Add_Flight:
            admin_add_flight(system);
            break;
        case Admin_Remove_Flight:
            admin_remove_flight(system);
            break;
        case Admin_Print_Flights:
            admin_print_flights(system);
            break;
        case Admin_Add_Airport:
            admin_add_airport(system);
            break;
        case Admin_Remove_Airport:
            admin_remove_airport(system);
            break;
        case Admin_Print_Airports:
            admin_print_airports(system);
            break;
        case Admin_Quit:
            loop = 0;
            break;
        case Admin_Option_Count:
            break;
        }
    }
}
