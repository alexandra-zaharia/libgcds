//
// Created by Alexandra Zaharia on 17/12/18.
//

#ifndef LIBGCDS_QUEUE_H
#define LIBGCDS_QUEUE_H

#include <stdbool.h>
#include "node.h"

typedef struct Queue Queue;

struct Queue {
    Node* first;                        // least recently added node
    Node* last;                         // most recently added node
    unsigned int size;                  // number of items in the queue

    void (*free)(Queue*);               // frees the queue
    bool (*is_empty)(Queue*);           // is the queue empty?

    int (*enqueue)(Queue*, void* data); // adds an item to the queue
    void* (*dequeue)(Queue*);           // removes an item from the queue
};

Queue* queue_create();

#endif //LIBGCDS_QUEUE_H
