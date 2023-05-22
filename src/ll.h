#ifndef LL_H
#define LL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

typedef struct LinkedList
{
    Node *head;
} LinkedList;

typedef struct
{
    Node *current;
    bool finished;
} Iterator;

Node *node_create(void *data, Node *next);

void ll_init(LinkedList *list);
void ll_push_back(LinkedList *list, void *data);
void ll_push_front(LinkedList *list, void *data);
int ll_sort(LinkedList *list, int (*compare)(void *, void *));

Iterator iter_create(LinkedList *list);
void iter_next(Iterator *iter);

#endif