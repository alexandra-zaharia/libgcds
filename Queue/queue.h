//
// Created by Alexandra Zaharia on 17/12/18.
//

#ifndef CDSLIB_QUEUE_H
#define CDSLIB_QUEUE_H

#include <stdbool.h>

typedef struct Node Node;

struct Node {
    void *data;
    Node *next;
};

typedef struct Queue Queue;

struct Queue {
    Node* first;                        // least recently added node
    Node* last;                         // most recently added node
    unsigned int size;                  // number of items in the linked list

    void (*free)(Queue*);               // frees the queue
    bool (*is_empty)(Queue*);           // is the queue empty?

    int (*enqueue)(Queue*, void* data); // adds an item to the queue
    void* (*dequeue)(Queue*);           // removes an item from the queue
};

Queue* queue_create();

#endif //CDSLIB_QUEUE_H
