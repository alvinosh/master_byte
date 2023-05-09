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
    UNUSED(system);
    printf("UNIMPLEMENTED \n");
}

void admin_remove_flight(System *system)
{
    UNUSED(system);
    printf("UNIMPLEMENTED \n");
}

void admin_print_flights(System *system)
{
    Flight flights[1024];
    int flight_count = 0;
    system_flight_get_all(system, flights, &flight_count);
    system_flight_print_all(flights, &flight_count);
}

void admin_add_airport(System *system)
{
    UNUSED(system);
    printf("UNIMPLEMENTED \n");
}

void admin_remove_airport(System *system)
{
    UNUSED(system);
    printf("UNIMPLEMENTED \n");
}

void admin_print_airports(System *system)
{
    UNUSED(system);
    printf("UNIMPLEMENTED \n");
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
