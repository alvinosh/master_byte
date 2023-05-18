#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "helper.h"
#include "system.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

typedef enum
{
    Customer_Search_Flights = 0,
    Customer_Flights_By_From_Airport,
    Customer_Flights_By_ID,
    Customer_Book_Flight,
    Customer_My_Bookings,
    Customer_Quit,
    Customer_Option_Count
} Customer_Option;

Customer_Option customer_option_get();
void customer_option_help();
void customer_run(System *system);

#endif