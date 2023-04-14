#include "admin.h"

Admin_Option admin_option_get()
{
    helper_prompt("");
    char c = helper_get_int();
    if (c == -1)
    {
        printf("Invalid Option. Please Try Again \n");
        return admin_option_get();
    }
    switch (c)
    {
    case 1:
        return Add_Flight;
    case 2:
        return Remove_Flight;
    case 3:
        return Add_Customer;
    case 4:
        return Remove_Customer;
    case 5:
        return Add_Reservation;
    case 6:
        return Remove_Reservation;
    case 7:
        return Print_Flights;
    case 8:
        return Print_Customers;
    case 9:
        return Print_Reservations;
    case 10:
        return Admin_Quit;
    default:
        printf("Invalid Option. Please Try Again \n");
        return admin_option_get();
    }
}

void admin_option_help()
{
    printf("Please Enter Your Option. \n");
    printf("    1. Add Flight \n");
    printf("    2. Remove Flight \n");
    printf("    3. Add Customer \n");
    printf("    4. Remove Customer \n");
    printf("    5. Add Reservation \n");
    printf("    6. Remove Reservation \n");
    printf("    7. Print Flights \n");
    printf("    8. Print Customers \n");
    printf("    9. Print Reservations \n");
    printf("    10. Quit \n");
}

void admin_authenticate()
{
    helper_prompt("Password");
    char line[256];

    if (fgets(line, sizeof line, stdin) != NULL)
    {
        line[strlen(line) - 1] = '\0';

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
    else
    {
        printf("Invalid Password. Please Try Again \n");
        admin_authenticate();
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
        case Add_Flight:
            printf("Add Flight \n");
            break;
        case Remove_Flight:
            printf("Remove Flight \n");
            break;
        case Add_Customer:
            printf("Add Customer \n");
            break;
        case Remove_Customer:
            printf("Remove Customer \n");
            break;
        case Add_Reservation:
            printf("Add Reservation \n");
            break;
        case Remove_Reservation:
            printf("Remove Reservation \n");
            break;
        case Print_Flights:
            printf("Print Flights \n");
            break;
        case Print_Customers:
            printf("Print Customers \n");
            break;
        case Print_Reservations:
            printf("Print Reservations \n");
            break;
        case Admin_Quit:
            printf("Quit \n");
            break;
        case Admin_Option_Count:
            break;
        }
    }
}