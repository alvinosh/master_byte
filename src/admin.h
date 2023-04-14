#ifndef ADMIN_H
#define ADMIN_H

#include "helper.h"
#include "pch.h"

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
    Admin_Quit,
    Admin_Option_Count
} Admin_Option;

Admin_Option admin_option_get();
void admin_option_help();
void admin_run();

#endif