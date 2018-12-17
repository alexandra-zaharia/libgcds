//
// Created by Alexandra Zaharia on 13/12/18.
//

#ifndef CDSLIB_STACK_H
#define CDSLIB_STACK_H

#include <stdbool.h>

typedef struct Item Item;

struct Item {
    void* data;
    Item* next;
};

typedef struct Stack Stack;

struct Stack {
    Item* top;                  // first item in the stack
    unsigned int size;          // number of items in the stack

    void (*free)(Stack*);       // frees the stack
    bool (*is_empty)(Stack*);   // is the stack empty?

    int (*push)(Stack*, void*); // adds an item on top of the stack
    void* (*pop)(Stack*);       // removes and returns item at top of stack
};

Stack* stack_create();

#endif //CDSLIB_STACK_H
