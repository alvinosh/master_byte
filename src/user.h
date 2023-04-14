#ifndef USER_H
#define USER_H

#include "helper.h"
#include "pch.h"

typedef enum
{
    Administrator = 0,
    Customer,
    User_Type_Count
} User_Type;

User_Type user_type_get();
void user_greet();

#endif