//
// Created by Alexandra Zaharia on 13/12/18.
//

#ifndef CDSLIB_LINKED_LIST_H
#define CDSLIB_LINKED_LIST_H

#include <stdbool.h>

typedef struct Node Node;

struct Node {
    void* data;
    Node* next;
    Node* prev;
};

typedef struct LinkedList LinkedList;

struct LinkedList {
    Node* head;                              // first node of the linked list
    Node* tail;                              // last node of the linked list
    unsigned int size;                       // number of items in the linked list

    void (*free)(LinkedList*);               // frees the stack
    bool (*is_empty)(LinkedList*);           // is the linked list empty?

    int (*insert_start)(LinkedList*, void*); // adds an item at the front of the linked list
    int (*insert_end)(LinkedList*, void*);   // adds an item at the end of the linked list
    int (*insert_at)(LinkedList*, void*, unsigned int); // adds an item at a specified position

    void* (*remove_start)(LinkedList*);      // removes and returns item at front of linked list
    void* (*remove_end)(LinkedList*);        // removes and returns item at end of linked list
    void* (*remove_at)(LinkedList*, unsigned int); // removes and returns item at specified position
};

LinkedList* linked_list_create();

#endif //CDSLIB_LINKED_LIST_H
