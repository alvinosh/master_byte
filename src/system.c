#include "system.h"

static const char *const SEQUENCE_FILE_NAME = "sequence.txt";

void system_init(System *system, char *file_name)
{
    // open file
    system->file_name = file_name;
    system_seq_init();
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
        return;
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

    flight->entity.id = system_seq_next(); // Get the current value and  Increment the value
    flight->entity.is_deleted = false;     // Set the is_deleted to false

    fprintf(file, "%d,%d,%s,%s,%s,%s,%s %s", flight->entity.id, flight->entity.is_deleted, flight->from_airport, flight->to_airport, flight->price, flight->date);
}
