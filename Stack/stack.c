//
// Created by Alexandra Zaharia on 13/12/18.
//

#include <stdlib.h>
#include "stack.h"

// Frees the stack.
void stack_free(Stack* stack)
{
    if (!stack) return;

    Item* item = stack->top;
    while (item) {
        Item* tmp = item;
        item = item->next;
        free(tmp);
    }

    free(stack);
}

// Returns true if the stack is empty, false otherwise.
bool stack_is_empty(Stack* stack)
{
    return stack->top == NULL;
}

// Inserts the item on top of the stack. Returns 0 for success and -1 for failure.
int stack_push(Stack* stack, void* data)
{
    if (!stack) return -1;

    Item* item = item_create(data);
    if (!item) return -1;

    if (!stack->top) {
        stack->top = item;
    } else {
        item->next = stack->top;
        stack->top = item;
    }

    ++stack->size;

    return 0;
}

// Removes and returns the item on top of the stack.
void* stack_pop(Stack* stack)
{
    if (!stack || !stack->top) return NULL;

    Item* item = stack->top;
    stack->top = stack->top->next;

    void* data = item->data;
    free(item);
    --stack->size;

    return data;
}

// Creates and returns a Stack*, or NULL in case of failure.
Stack* stack_create()
{
    Stack* stack = malloc(sizeof(Stack));
    if (!stack) return NULL;

    stack->top = NULL;
    stack->size = 0;

    stack->free = stack_free;
    stack->is_empty = stack_is_empty;
    stack->push = stack_push;
    stack->pop = stack_pop;

    return stack;
}
