#include "pch.h"
#include "helper.h"
#include "user.h"
#include "admin.h"
#include "customer.h"
#include "system.h"

static const char *const DB_NAME = "db.txt";

int main(void)
{

    System system = {0};
    system_init(&system, (char *)DB_NAME);

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