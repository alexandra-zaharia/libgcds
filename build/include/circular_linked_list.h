//
// Created by Alexandra Zaharia on 26/01/19.
//

#ifndef LIBGCDS_CIRCULAR_LINKED_LIST_H
#define LIBGCDS_CIRCULAR_LINKED_LIST_H

#include <stdbool.h>
#include "node.h"

typedef struct CircularLinkedList CircularLinkedList;

struct CircularLinkedList {
    DNode* head;                             // first node of the circular linked list
    DNode* tail;                             // last node of the circular linked list
    unsigned int size;                       // number of items in the circular linked list

    void (*free)(CircularLinkedList*);       // frees the circular linked list
    bool (*is_empty)(CircularLinkedList*);   // is the circular linked list empty?

    int (*insert_start)(CircularLinkedList*, void*); // adds an item at the front of the linked list
    int (*insert_end)(CircularLinkedList*, void*);   // adds an item at the end of the linked list
    int (*insert_at)(CircularLinkedList*, void*, int); // adds an item at a given position

    void* (*remove_start)(CircularLinkedList*);        // removes and returns item at front of list
    void* (*remove_end)(CircularLinkedList*);          // removes and returns item at end of list
    void* (*remove_at)(CircularLinkedList*, int);      // removes and returns item at position

    bool (*contains)(CircularLinkedList*, void*);      // does the list contain a given item?
};

CircularLinkedList* circular_linked_list_create();

#endif //LIBGCDS_CIRCULAR_LINKED_LIST_H
