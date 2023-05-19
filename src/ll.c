#include "ll.h"

Node *node_create(void *data, Node *next)
{
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = next;
    return node;
}

void ll_init(LinkedList *list)
{
    list->head = NULL;
}

void ll_push_front(LinkedList *list, void *data)
{
    Node *node = node_create(data, list->head);
    list->head = node;
}

void ll_push_back(LinkedList *list, void *data)
{
    Node *node = node_create(data, NULL);
    if (list->head == NULL)
    {
        list->head = node;
        return;
    }

    Node *current = list->head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = node;
}

Iterator iter_create(LinkedList *list)
{
    Iterator iter = {0};
    iter.current = list->head;
    iter.finished = false;
    return iter;
}

void iter_next(Iterator *iter)
{
    if (iter->current->next != NULL)
    {
        iter->current = iter->current->next;
    }
    else
    {
        iter->finished = true;
    }
}

// typedef struct
// {
//     int id;
//     int isDeleted;
//     char name[1000];
// } Entity;

// int main()
// {
//     LinkedList list;
//     init_linked_list(&list);

//     Entity a = {0};
//     a.id = 1;
//     a.isDeleted = 0;
//     strcpy(a.name, "Test");

//     push_front(&list, &a);

//     for (Iterator i = iter_create(&list); !i.finished; iter_next(&i))
//     {
//         Entity *entity = ((Entity *)i.current->data);
//         printf("NODE: %d %d %s", entity->id, entity->isDeleted, entity->name);
//     }

//     return 0;
// }
