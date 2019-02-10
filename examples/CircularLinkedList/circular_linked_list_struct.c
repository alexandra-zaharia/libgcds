//
// Created by Alexandra Zaharia on 27/01/19.
//

#include <stdlib.h>
#include <stdio.h>
#include "circular_linked_list.h"

void list_point_print(CircularLinkedList* list);

typedef struct {
    int x;
    int y;
} Point;

int main()
{
    CircularLinkedList* list = circular_linked_list_create();
    if (!list) {
        fprintf(stderr, "Cannot allocate circular linked list.\n");
        exit(EXIT_FAILURE);
    }

    Point p1 = {.x = 1, .y = 10};
    Point p2 = {.x = 2, .y = 20};
    Point p3 = {.x = 3, .y = 30};

    int status;
    status = list->insert_end(list, &p1);
    printf("Status: %2d | Item(s): %d | Empty? %d | ", status, list->size, list->is_empty(list));
    list_point_print(list);
    status = list->insert_end(list, &p2);
    printf("Status: %2d | Item(s): %d | Empty? %d | ", status, list->size, list->is_empty(list));
    list_point_print(list);
    status = list->insert_end(list, &p3);
    printf("Status: %2d | Item(s): %d | Empty? %d | ", status, list->size, list->is_empty(list));
    list_point_print(list);

    for (int i = 0; i < 3; i++) {
        Point* p = (Point*) list->remove_start(list);
        printf("Popped: (%d, %d) | Item(s): %d | Empty? %d ",
               p->x, p->y, list->size, list->is_empty(list));
        list_point_print(list);
    }

    list->free(list);
}

void list_point_print(CircularLinkedList* list)
{
    if (!list || list->is_empty(list)) return;
    DNode* node = list->head;
    do {
        Point* p = (Point*) node->data;
        printf("(%d, %d) ", p->x, p->y);
        node = node->next;
    } while (node && node != list->head);
    printf("\n");
}