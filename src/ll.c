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
    return iter;
}

void iter_next(Iterator *iter)
{
    iter->current = iter->current->next;
}

// this function finds the node at the given index and puts it at data and returns 0 if successful, and -1 if not
int ll_get_at_index(LinkedList *list, void *data, int index)
{
    if (index < 0)
    {
        return -1;
    }

    int i = 0;
    for (Iterator iter = iter_create(list); iter.current != NULL; iter_next(&iter))
    {
        if (i == index)
        {
            data = iter.current->data;
            return 0;
        }
        i++;
    }

    return -1;
}

int ll_swap(LinkedList *list, int index_a, int index_b)
{
    if (index_a < 0 || index_b < 0)
    {
        return -1;
    }

    if (index_a == index_b)
    {
        return 0;
    }

    Node *node_a = NULL;
    Node *node_b = NULL;

    int i = 0;
    for (Iterator iter = iter_create(list); iter.current != NULL; iter_next(&iter))
    {
        if (i == index_a)
        {
            node_a = iter.current;
        }
        else if (i == index_b)
        {
            node_b = iter.current;
        }

        if (node_a != NULL && node_b != NULL)
        {
            void *temp = node_a->data;
            node_a->data = node_b->data;
            node_b->data = temp;
            return 0;
        }
        i++;
    }

    return -1;
}

int ll_sort(LinkedList *list, int (*compare)(void *, void *))
{
    int swapped = 0;
    do
    {
        swapped = 0;
        for (Iterator iter = iter_create(list); iter.current != NULL; iter_next(&iter))
        {
            if (iter.current->next != NULL && compare(iter.current->data, iter.current->next->data) > 0)
            {
                void *temp = iter.current->data;
                iter.current->data = iter.current->next->data;
                iter.current->next->data = temp;
                swapped = 1;
            }
        }
    } while (swapped);

    return 0;
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

//     for (Iterator i = iter_create(&list); i.current != NULL; iter_next(&i))
//     {
//         Entity *entity = ((Entity *)i.current->data);
//         printf("NODE: %d %d %s", entity->id, entity->isDeleted, entity->name);
//     }

//     return 0;
// }
