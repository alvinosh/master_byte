#ifndef ADMIN_H
#define ADMIN_H

#include "helper.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

#include "system.h"

typedef enum
{
    Admin_Add_Flight = 0,
    Admin_Remove_Flight,
    Admin_Print_Flights,

    Admin_Add_Airport,
    Admin_Remove_Airport,
    Admin_Print_Airports,

    Admin_Quit,
    Admin_Option_Count
} Admin_Option;

Admin_Option admin_option_get();
void admin_option_help();
void admin_run(System *system);

#endif