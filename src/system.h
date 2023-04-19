#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 128

typedef struct
{
    char *file_name;
} System;

typedef struct
{
    int id;
    bool is_deleted;
} Entity;

typedef struct
{
    Entity entity;
    char name[MAX_STRING_SIZE];
    char code[MAX_STRING_SIZE];
    char country[MAX_STRING_SIZE];
    char city[MAX_STRING_SIZE];
} Airport;

typedef struct
{
    Entity entity;
    char from_airport[MAX_STRING_SIZE];
    char to_airport[MAX_STRING_SIZE];
    char price[MAX_STRING_SIZE];
    char date[MAX_STRING_SIZE];
} Flight;

typedef struct
{
    Entity entity;
    int flight_id;
    char first_name[MAX_STRING_SIZE];
    char last_name[MAX_STRING_SIZE];
} Booking;

void system_init(System *system, char *file_name);

void system_flight_get_all(System *system, Flight *flights, int *flight_count);
void system_flight_add(System *system, Flight *flight);
void system_flight_remove(System *system, int flight_id);
void system_flight_edit(System *system, int flight_id, Flight *flight);
void system_flight_print_all(Flight *flight, int *flight_count);

void system_airport_get_all(System *system, Airport *airports, int *airport_count);
void system_airport_add(System *system, Airport *airport);
void system_airport_remove(System *system, int airport_id);
void system_airport_edit(System *system, int airport_id, Airport *airport);

void system_booking_get_all(System *system, Booking *bookings, int *booking_count);
void system_booking_add(System *system, Booking *booking);
void system_booking_remove(System *system, int booking_id);
void system_booking_edit(System *system, int booking_id, Booking *booking);

void system_seq_init();
int system_seq_current();
int system_seq_next();

#endif