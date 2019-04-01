//
// Created by Alexandra Zaharia on 13/12/18.
//

#ifndef LIBGCDS_STACK_H
#define LIBGCDS_STACK_H

#include <stdbool.h>
#include "node.h"

typedef struct Stack Stack;

struct Stack {
    Item* top;                       // first item in the stack
    unsigned int size;               // number of items in the stack

    void (*free)(Stack*);            // frees the stack
    bool (*is_empty)(Stack*);        // is the stack empty?

    int (*push)(Stack*, void*);      // adds an item on top of the stack
    void* (*pop)(Stack*);            // removes and returns item at top of stack

    bool (*contains)(Stack*, void*); // does the stack contain a given item?
};

Stack* stack_create();

#endif //LIBGCDS_STACK_H
