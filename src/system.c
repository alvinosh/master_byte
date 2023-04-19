#include "system.h"
#include "helper.h"

static const char *const SEQUENCE_FILE_NAME = "sequence.txt";

static char SYSTEM_FLIGHT = 'F';
static char SYSTEM_AIRPORT = 'A';
// static char SYSTEM_BOOKING = 'B';

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
        fprintf(stderr, "Error opening file.\n");
        exit(1);
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
                token = strtok(NULL, ",");
                strcpy(flights[i].from_airport, token);
                token = strtok(NULL, ",");
                strcpy(flights[i].to_airport, token);
                token = strtok(NULL, ",");
                strcpy(flights[i].price, token);
                token = strtok(NULL, ",");
                strcpy(flights[i].date, token);
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
                        token = strtok(NULL, ",");
                        strcpy(flights[i].from_airport, token);
                        token = strtok(NULL, ",");
                        strcpy(flights[i].to_airport, token);
                        token = strtok(NULL, ",");
                        strcpy(flights[i].price, token);
                        token = strtok(NULL, ",");
                        strcpy(flights[i].date, token);
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

void system_flight_print_all(Flight *flight, int *flight_count)
{
    for (int i = 0; i < *flight_count; i++)
    {
        if (!flight[i].entity.is_deleted)
        {
            printf("Flight ID: %d\n", flight[i].entity.id);
            printf("    From Airport: %s\n", flight[i].from_airport);
            printf("    To Airport: %s\n", flight[i].to_airport);
            printf("    Price: %s\n", flight[i].price);
            printf("    Date: %s\n", flight[i].date);
        }
    }
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
                token = strtok(NULL, ",");
                strcpy(airports[i].name, token);
                token = strtok(NULL, ",");
                strcpy(airports[i].city, token);
                token = strtok(NULL, ",");
                strcpy(airports[i].code, token);
                token = strtok(NULL, ",");
                strcpy(airports[i].country, token);
                airports[i].entity.is_deleted = false;
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
                        token = strtok(NULL, ",");
                        strcpy(airports[i].name, token);
                        token = strtok(NULL, ",");
                        strcpy(airports[i].city, token);
                        token = strtok(NULL, ",");
                        strcpy(airports[i].code, token);
                        token = strtok(NULL, ",");
                        strcpy(airports[i].country, token);
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

void system_airport_print_all(Airport *airports, int *airport_count)
{
    for (int i = 0; i < *airport_count; i++)
    {
        if (!airports[i].entity.is_deleted)
        {
            printf("Airport ID: %d\n", airports[i].entity.id);
            printf("    Name: %s\n", airports[i].name);
            printf("    City: %s\n", airports[i].city);
            printf("    Code: %s\n", airports[i].code);
            printf("    Country: %s\n", airports[i].country);
        }
    }
}
