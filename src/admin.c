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
            system_entity_remove(system, SYSTEM_FLIGHT, *flight_id);
            printf("Flight Removed \n");
}

void admin_print_flights(System *system)
{

    LinkedList flights;
    ll_init(&flights);

    system_entity_get_all(system, SYSTEM_FLIGHT, &flights);
    system_entity_print_all(SYSTEM_FLIGHT, &flights);
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
    if(strlen(code) != 3){
        printf("Invalid Option. Code must be 3 letters. Please Try Again \n");
        return;
    }
    LinkedList *airports;
    ll_init(airports);
    system_entity_get_all(system, SYSTEM_AIRPORT, airports);
    for (Iterator i = iter_create(airports); !i.finished; iter_next(&i))
    {
        Airport *airPort = ((Airport *)i.current->data);

        if (strcmp(code,airPort->code)==0)
        {
            printf("Error. Code must be unique. Airport already exists. Please Try Again \n");
            return;
        }
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
    LinkedList *airports=malloc(sizeof(LinkedList));
    ll_init(airports);
    system_entity_get_all(system, SYSTEM_AIRPORT, airports);
    for (Iterator i = iter_create(airports); !i.finished; iter_next(&i))
    {
        Airport *airport = ((Airport *)i.current->data);

        if (*airport_id==airport->entity.id)
        {
            system_entity_remove(system, SYSTEM_AIRPORT, *airport_id);
            printf("Airport Removed \n");
            return;
        }
    }
    printf("Invalid ID. Please try again \n");
    return;
}

void admin_print_airports(System *system)
{
    LinkedList airports;
    ll_init(&airports);
    system_entity_get_all(system, SYSTEM_AIRPORT, &airports);
    system_entity_print_all(SYSTEM_AIRPORT, &airports);
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
