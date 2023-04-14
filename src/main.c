#include "stdio.h"

typedef enum
{
    Administrator = 0,
    Customer,
    User_Type_Count
} User_Type;

void user_greet()
{
    printf("Welcome To The Master Byte Flight Rservations System. \n");
    printf("Please Enter Your User Type. \n");
    printf("    1. Administrator \n");
    printf("    2. Customer \n");
}

void user_prompt(char *message)
{
    printf("%s > ", message);
}

User_Type user_type_get()
{
    user_prompt("");
    int type;
    scanf("%d", &type);
    switch (type - 1)
    {
    case Administrator:
        return Administrator;
    case Customer:
        return Customer;
    default:
        printf("Invalid User Type. Please Try Again \n");
        user_type_get();
    }
}

typedef enum
{
    Add_Flight = 0,
    Remove_Flight,
    Add_Customer,
    Remove_Customer,
    Add_Reservation,
    Remove_Reservation,
    Print_Flights,
    Print_Customers,
    Print_Reservations,
    Quit,
    Admin_Option_Count
} Admin_Option;

Admin_Option admin_option_get()
{
    user_prompt("");
    int option;
    scanf("%d", &option);
    switch (option - 1)
    {
    case Add_Flight:
        return Add_Flight;
    case Remove_Flight:
        return Remove_Flight;
    case Add_Customer:
        return Add_Customer;
    case Remove_Customer:
        return Remove_Customer;
    case Add_Reservation:
        return Add_Reservation;
    case Remove_Reservation:
        return Remove_Reservation;
    case Print_Flights:
        return Print_Flights;
    case Print_Customers:
        return Print_Customers;
    case Print_Reservations:
        return Print_Reservations;
    case Quit:
        return Quit;
    default:
        printf("Invalid Option. Please Try Again \n");
        admin_option_get();
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

void admin_run()
{
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
        case Quit:
            printf("Quit \n");
            return;
        }
    }
}

typedef enum
{
    Search_Flights = 0,
    Book_Flight,
    Quit,
    Customer_Option_Count
} Customer_Option;

Customer_Option customer_option_get()
{
    user_prompt("");
    int option;
    scanf("%d", &option);
    switch (option - 1)
    {
    case Search_Flights:
        return Search_Flights;
    case Book_Flight:
        return Book_Flight;
    case Quit:
        return Quit;
    default:
        printf("Invalid Option. Please Try Again \n");
        customer_option_get();
    }
}

void customer_option_help()
{
    printf("Please Enter Your Option. \n");
    printf("    1. Search Flights \n");
    printf("    2. Book Flight \n");
    printf("    3. Quit \n");
}

void customer_run()
{
    customer_option_help();
    while (1)
    {
        Customer_Option option = customer_option_get();
        switch (option)
        {
        case Search_Flights:
            printf("Search Flights \n");
            break;
        case Book_Flight:
            printf("Book Flight \n");
            break;
        case Quit:
            printf("Quit \n");
            return;
        }
    }
}

int main(int argc, char *argv[])
{
    user_greet();
    User_Type user_type = user_type_get();
    if (user_type == Administrator)
    {
        admin_run();
    }
    else if (user_type == Customer)
    {
        customer_run();
    }
}