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

void admin_add_flight()
{
    printf("UNIMPLEMENTED \n");
}

void admin_remove_flight()
{
    printf("UNIMPLEMENTED \n");
}

void admin_print_flights()
{
    printf("UNIMPLEMENTED \n");
}

void admin_add_airport()
{
    printf("UNIMPLEMENTED \n");
}

void admin_remove_airport()
{
    printf("UNIMPLEMENTED \n");
}

void admin_print_airports()
{
    printf("UNIMPLEMENTED \n");
}

Admin_Option admin_option_get()
{
    helper_prompt("");
    char c = helper_get_int();
    if (c == -1)
    {
        printf("Invalid Option. Please Try Again \n");
        return admin_option_get();
    }
    if (c - 1 >= 0 && c - 1 < Admin_Option_Count)
    {
        return c - 1;
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
}

void admin_authenticate()
{
    helper_prompt("Password");
    char line[256] = helper_get_string();

    if (line == -1)
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

void admin_run()
{
    admin_authenticate();
    admin_option_help();
    while (1)
    {
        Admin_Option option = admin_option_get();
        switch (option)
        {
        case Admin_Add_Flight:
            admin_add_flight();
            break;
        case Admin_Remove_Flight:
            admin_remove_flight();
            break;
        case Admin_Print_Flights:
            admin_print_flights();
            break;
        case Admin_Add_Airport:
            admin_add_airport();
            break;
        case Admin_Remove_Airport:
            admin_remove_airport();
            break;
        case Admin_Print_Airports:
            admin_print_airports();
            break;
        case Admin_Quit:
            printf("Quit \n");
            break;
        case Admin_Option_Count:
            break;
        }
    }
}
