//
// Created by Alexandra Zaharia on 20/12/18.
//

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

void stack_point_print(Stack* stack);

typedef struct {
    int x;
    int y;
} Point;

int main()
{
    Stack* stack = stack_create();
    if (!stack) {
        fprintf(stderr, "Cannot allocate stack.\n");
        exit(EXIT_FAILURE);
    }

    Point p1 = {.x = 1, .y = 10};
    Point p2 = {.x = 2, .y = 20};
    Point p3 = {.x = 3, .y = 30};

    int status;
    status = stack->push(stack, &p1);
    printf("Status: %2d | Item(s): %d | Empty? %d | ", status, stack->size, stack->is_empty(stack));
    stack_point_print(stack);
    status = stack->push(stack, &p2);
    printf("Status: %2d | Item(s): %d | Empty? %d | ", status, stack->size, stack->is_empty(stack));
    stack_point_print(stack);
    status = stack->push(stack, &p3);
    printf("Status: %2d | Item(s): %d | Empty? %d | ", status, stack->size, stack->is_empty(stack));
    stack_point_print(stack);

    for (int i = 0; i < 3; i++) {
        Point* p = (Point*) stack->pop(stack);
        printf("Popped: (%d, %d) | Item(s): %d | Empty? %d ",
               p->x, p->y, stack->size, stack->is_empty(stack));
        stack_point_print(stack);
    }

    stack->free(stack);
}

void stack_point_print(Stack* stack)
{
    if (!stack || !stack->top) return;
    Item* item = stack->top;
    while (item) {
        Point* p = (Point*) item->data;
        printf("(%d, %d) ", p->x, p->y);
        item = item->next;
    }
    printf("\n");
}