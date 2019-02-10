//
// Created by Alexandra Zaharia on 20/12/18.
//

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

void print(Stack* stack);

int main()
{
    Stack* stack = stack_create();
    if (!stack) {
        fprintf(stderr, "Cannot allocate stack.\n");
        exit(EXIT_FAILURE);
    }

    int val[] = {1, 2, 3};
    int i;

    for (i = 0; i < 3; i++) {
        int status = stack->push(stack, &val[i]);
        printf("Status: %2d | Item(s): %d | Empty? %d | ",
               status, stack->size, stack->is_empty(stack));
        print(stack);
    }
    for (i = 0; i < 3; i++) {
        int value = *((int*) stack->pop(stack));
        printf("Value: %d | Item(s): %d | Empty? %d | ",
               value, stack->size, stack->is_empty(stack));
        print(stack);
    }

    stack->free(stack);
}

void print(Stack* stack)
{
    if (!stack || !stack->top) return;
    Item* item = stack->top;
    while (item) {
        printf("%d ", *((int*) item->data));
        item = item->next;
    }
    printf("\n");
}