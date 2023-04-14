#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "helper.h"
#include "pch.h"

typedef enum
{
    Search_Flights = 0,
    Book_Flight,
    Customer_Quit,
    Customer_Option_Count
} Customer_Option;

Customer_Option customer_option_get();
void customer_option_help();
void customer_run();

#endif