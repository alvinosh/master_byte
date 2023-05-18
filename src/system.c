#include "system.h"
#include "helper.h"

static const char *const SEQUENCE_FILE_NAME = "./sequence.txt";

static char SYSTEM_FLIGHT = 'F';
static char SYSTEM_AIRPORT = 'A';
static char SYSTEM_BOOKING = 'B';

static char SYSTEM_CREATE = 'C';
static char SYSTEM_UPDATE = 'U';
static char SYSTEM_DELETE = 'D';

void system_init(System *system, char *file_name)
{
    // open file
    system->file_name = file_name;
    // system_seq_init();
}

void system_seq_init()
{
    FILE *file = fopen(SEQUENCE_FILE_NAME, "w"); // Open the file in write mode
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }
    fprintf(file, "%d", 0); // Write the initial value to the file
    fclose(file);           // Close the file
}

int system_seq_current()
{
    FILE *file = fopen(SEQUENCE_FILE_NAME, "r"); // Open the file in read mode
    if (file == NULL)
    {
        system_seq_init();
        fprintf(stderr, "Sequence File Regenerated.\n");
        file = fopen(SEQUENCE_FILE_NAME, "r");

        if (file == NULL)
        {
            fprintf(stderr, "Error opening file.\n");
            exit(1);
        };

        // exit(1);
    }
    int num;
    fscanf(file, "%d", &num); // Read the number from the file
    fclose(file);             // Close the file
    return num;
}

int system_seq_next()
{
    int num = system_seq_current(); // Get the current value
    if (num == -1)
    {
        fprintf(stderr, "Error getting current value.\n");
        exit(1);
    }
    num++;                                       // Increment the value
    FILE *file = fopen(SEQUENCE_FILE_NAME, "w"); // Open the file in write mode
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }
    fprintf(file, "%d", num); // Write the updated value to the file
    fclose(file);             // Close the file
    return num;
}

void system_flight_schema(Flight *flight, char *token)
{
    token = strtok(NULL, ",");
    strcpy(flight->from_airport, token);
    token = strtok(NULL, ",");
    strcpy(flight->to_airport, token);
    token = strtok(NULL, ",");
    strcpy(flight->price, token);
    token = strtok(NULL, ",");
    strcpy(flight->date, token);
}

void system_flight_add(System *system, Flight *flight)
{

    FILE *file = fopen(system->file_name, "a"); // Open the file in append mode
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }

    flight->entity.id = system_seq_next();                                                                                                                            // Get the current value and  Increment the value
    flight->entity.is_deleted = false;                                                                                                                                // Set the is_deleted to false
    fprintf(file, "%c,%c,%d,%s,%s,%s,%s;\n", SYSTEM_FLIGHT, SYSTEM_CREATE, flight->entity.id, flight->from_airport, flight->to_airport, flight->price, flight->date); // Write the flight to the file
    fclose(file);                                                                                                                                                     // Close the file
}

void system_flight_get_all(System *system, Flight *flights, int *flight_count)
{
    FILE *file = fopen(system->file_name, "r"); // Open the file in read mode
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }

    char line[1024];
    int i = 0;
    while (fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, ",");
        if (token[0] == SYSTEM_FLIGHT)
        {
            token = strtok(NULL, ",");
            if (token[0] == SYSTEM_CREATE)
            {
                token = strtok(NULL, ",");
                flights[i].entity.id = atoi(token);

                system_flight_schema(&flights[i], token);

                flights[i]
                    .entity.is_deleted = false;
                i++;
            }
            else if (token[0] == SYSTEM_DELETE)
            {
                token = strtok(NULL, ",");
                int id = atoi(token);
                for (int j = 0; j < i; j++)
                {
                    if (flights[j].entity.id == id)
                    {
                        flights[j].entity.is_deleted = true;
                    }
                }
            }
            else if (token[0] == SYSTEM_UPDATE)
            {
                token = strtok(NULL, ",");
                int id = atoi(token);
                for (int j = 0; j < i; j++)
                {
                    if (flights[j].entity.id == id)
                    {
                        system_flight_schema(&flights[i], token);
                    }
                }
            }
        }
    }
    *flight_count = i;
    fclose(file); // Close the file
}

void system_flight_remove(System *system, int flight_id)
{
    FILE *file = fopen(system->file_name, "a"); // Open the file in append mode
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }
    fprintf(file, "%c,%c,%d,\n", SYSTEM_FLIGHT, SYSTEM_DELETE, flight_id); // Write the flight to the file
    fclose(file);                                                          // Close the file
}

void system_flight_edit(System *system, int flight_id, Flight *flight)
{
    FILE *file = fopen(system->file_name, "a"); // Open the file in append mode
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }
    fprintf(file, "%c,%c,%d,%s,%s,%s,%s;\n", SYSTEM_FLIGHT, SYSTEM_UPDATE, flight_id, flight->from_airport, flight->to_airport, flight->price, flight->date); // Write the flight to the file
    fclose(file);                                                                                                                                             // Close the file
}

void system_flight_print_one(Flight *flight)
{
    printf("Flight ID: %d\n", flight->entity.id);
    printf("    From Airport: %s\n", flight->from_airport);
    printf("    To Airport: %s\n", flight->to_airport);
    printf("    Price: %s\n", flight->price);
    printf("    Date: %s\n", flight->date);
}

void system_flight_print_all(Flight *flight, int *flight_count)
{
    for (int i = 0; i < *flight_count; i++)
    {
        if (!flight[i].entity.is_deleted)
        {
            system_flight_print_one(&flight[i]);
        }
    }
}

void system_airport_schema(Airport *airport, char *token)
{
    token = strtok(NULL, ",");
    strcpy(airport->name, token);
    token = strtok(NULL, ",");
    strcpy(airport->city, token);
    token = strtok(NULL, ",");
    strcpy(airport->code, token);
    token = strtok(NULL, ",");
    strcpy(airport->country, token);
}

void system_airport_get_all(System *system, Airport *airports, int *airport_count)
{
    FILE *file = fopen(system->file_name, "r"); // Open the file in read mode
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }

    char line[1024];
    int i = 0;
    while (fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, ",");
        if (token[0] == SYSTEM_AIRPORT)
        {
            token = strtok(NULL, ",");
            if (token[0] == SYSTEM_CREATE)
            {
                token = strtok(NULL, ",");
                airports[i].entity.id = atoi(token);

                system_airport_schema(&airports[i], token);

                airports[i]
                    .entity.is_deleted = false;
                i++;
            }
            else if (token[0] == SYSTEM_DELETE)
            {
                token = strtok(NULL, ",");
                int id = atoi(token);
                for (int j = 0; j < i; j++)
                {
                    if (airports[j].entity.id == id)
                    {
                        airports[j].entity.is_deleted = true;
                    }
                }
            }
            else if (token[0] == SYSTEM_UPDATE)
            {
                token = strtok(NULL, ",");
                int id = atoi(token);
                for (int j = 0; j < i; j++)
                {
                    if (airports[j].entity.id == id)
                    {
                        system_airport_schema(&airports[i], token);
                    }
                }
            }
        }
    }
    *airport_count = i;
    fclose(file); // Close the file
}

void system_airport_add(System *system, Airport *airport)
{
    FILE *file = fopen(system->file_name, "a"); // Open the file in append mode
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }
    airport->entity.id = system_seq_next(); // Get the current value and  Increment the value
    airport->entity.is_deleted = false;
    fprintf(file, "%c,%c,%d,%s,%s,%s,%s;\n", SYSTEM_AIRPORT, SYSTEM_CREATE, airport->entity.id, airport->name, airport->city, airport->code, airport->country); // Write the airport to the file
    fclose(file);                                                                                                                                               // Close the file
}

void system_airport_remove(System *system, int airport_id)
{
    FILE *file = fopen(system->file_name, "a"); // Open the file in append mode
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }
    fprintf(file, "%c,%c,%d,\n", SYSTEM_AIRPORT, SYSTEM_DELETE, airport_id); // Write the airport to the file
    fclose(file);                                                            // Close the file
}

void system_airport_edit(System *system, int airport_id, Airport *airport)
{
    FILE *file = fopen(system->file_name, "a"); // Open the file in append mode
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }
    fprintf(file, "%c,%c,%d,%s,%s,%s,%s;\n", SYSTEM_AIRPORT, SYSTEM_UPDATE, airport_id, airport->name, airport->city, airport->code, airport->country); // Write the airport to the file
    fclose(file);                                                                                                                                       // Close the file
}

void system_airport_print_one(Airport *airport)
{
    printf("Airport ID: %d\n", airport->entity.id);
    printf("    Name: %s\n", airport->name);
    printf("    City: %s\n", airport->city);
    printf("    Code: %s\n", airport->code);
    printf("    Country: %s\n", airport->country);
}

void system_airport_print_all(Airport *airports, int *airport_count)
{
    for (int i = 0; i < *airport_count; i++)
    {
        if (!airports[i].entity.is_deleted)
        {
            system_airport_print_one(&airports[i]);
        }
    }
}

void system_booking_schema(Booking *booking, char *token)
{

    token = strtok(NULL, ",");
    booking->flight_id = atoi(token);
    token = strtok(NULL, ",");
    strcpy(booking->first_name, token);
    token = strtok(NULL, ",");
    strcpy(booking->last_name, token);
}

void system_booking_get_all(System *system, Booking *bookings, int *booking_count)
{
    FILE *file = fopen(system->file_name, "r"); // Open the file in read mode
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }

    char line[1024];
    int i = 0;
    while (fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, ",");
        if (token[0] == SYSTEM_BOOKING)
        {
            token = strtok(NULL, ",");
            if (token[0] == SYSTEM_CREATE)
            {
                token = strtok(NULL, ",");
                bookings[i].entity.id = atoi(token);

                system_booking_schema(&bookings[i], token);

                bookings[i].entity.is_deleted = false;
                i++;
            }
            else if (token[0] == SYSTEM_DELETE)
            {
                token = strtok(NULL, ",");
                int id = atoi(token);
                for (int j = 0; j < i; j++)
                {
                    if (bookings[j].entity.id == id)
                    {
                        bookings[j].entity.is_deleted = true;
                    }
                }
            }
            else if (token[0] == SYSTEM_UPDATE)
            {
                token = strtok(NULL, ",");
                int id = atoi(token);
                for (int j = 0; j < i; j++)
                {
                    if (bookings[j].entity.id == id)
                    {
                        system_booking_schema(&bookings[i], token);
                    }
                }
            }
        }
    }
    *booking_count = i;
    fclose(file); // Close the file
}

void system_booking_add(System *system, Booking *booking)
{
    FILE *file = fopen(system->file_name, "a"); // Open the file in append mode
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }
    booking->entity.id = system_seq_next(); // Get the current value and  Increment the value
    booking->entity.is_deleted = false;
    fprintf(file, "%c,%c,%d,%d,%s,%s;\n", SYSTEM_BOOKING, SYSTEM_CREATE, booking->entity.id, booking->flight_id, booking->first_name, booking->last_name); // Write the booking to the file
    fclose(file);                                                                                                                                          // Close the file
}

void system_booking_remove(System *system, int booking_id)
{
    FILE *file = fopen(system->file_name, "a"); // Open the file in append mode
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }
    fprintf(file, "%c,%c,%d,\n", SYSTEM_BOOKING, SYSTEM_DELETE, booking_id); // Write the booking to the file
    fclose(file);                                                            // Close the file
}

void system_booking_edit(System *system, int booking_id, Booking *booking)
{
    FILE *file = fopen(system->file_name, "a"); // Open the file in append mode
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }
    fprintf(file, "%c,%c,%d,%d,%s,%s;\n", SYSTEM_BOOKING, SYSTEM_UPDATE, booking_id, booking->flight_id, booking->first_name, booking->last_name); // Write the booking to the file
    fclose(file);                                                                                                                                  // Close the file
}

void system_booking_print_one(Booking *booking)
{
    printf("Booking ID: %d\n", booking->entity.id);
    printf("    Flight ID: %d\n", booking->flight_id);
    printf("    First Name: %s\n", booking->first_name);
    printf("    Last Name: %s\n", booking->last_name);
}
void system_booking_print_all(Booking *bookings, int *booking_count)
{
    for (int i = 0; i < *booking_count; i++)
    {
        if (!bookings[i].entity.is_deleted)
        {
            system_booking_print_one(&bookings[i]);
        }
    }
}