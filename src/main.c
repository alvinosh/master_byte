#include "pch.h"
#include "helper.h"
#include "user.h"
#include "admin.h"
#include "customer.h"

int main(void)
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