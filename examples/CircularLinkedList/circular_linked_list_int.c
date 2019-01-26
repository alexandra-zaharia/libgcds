//
// Created by Alexandra Zaharia on 27/01/19.
//

#include <stdlib.h>
#include <stdio.h>
#include "circular_linked_list.h"

void print(CircularLinkedList* list);

int main()
{
    CircularLinkedList* list = circular_linked_list_create();
    if (!list) {
        fprintf(stderr, "Cannot allocate circular linked list.\n");
        exit(EXIT_FAILURE);
    }

    int status, i;
    int val[] = {1, 2, 3};

    for (i = 0; i < 3; i++) {
        status = list->insert_end(list, &val[i]);
        printf("Status: %2d | Item(s): %d | Empty? %d | ",
               status, list->size, list->is_empty(list));
        print(list);
    }
    for (i = 0; i < 3; i++) {
        int value = *((int*) list->remove_start(list));
        printf("Value: %d | Item(s): %d | Empty? %d | ",
               value, list->size, list->is_empty(list));
        print(list);
    }

    list->free(list);
}

void print(CircularLinkedList* list)
{
    if (!list || list->is_empty(list)) return;
    DNode* node = list->head;
    while (node && node->next != list->head) {
        printf("%d ", *((int*) node->data));
        node = node->next;
    }
    if (node) printf("%d ", *((int*) node->data));
    printf("\n");
}