# Generic stack implementation

This is a generic stack implementation. A stack is a LIFO (last in, first out) data structure that supports two main operations: adding data on top of the stack (`push`) and retrieving the topmost item on the stack (`pop`). Additionally, it should be possible to know a stack's `size` and whether it `is_empty`. 

## API

`Stack` has the following API:
  * `Stack* stack_create()` -- Creates a new `Stack` and returns a pointer to it, or `NULL` in case of failure.
  * `stack->free(stack)` -- Frees the given `stack`.
  * `stack->is_empty(stack)` -- Returns `true` if the `stack` is empty, `false` otherwise.
  * `stack->push(stack, void* item)` -- Adds the `item` on top of the `stack`. Returns 0 on success and -1 on failure.
  * `stack->pop(stack)` -- Removes and returns the item on top of the `stack`. Returns `NULL` if the stack is null or empty.

## Usage example with integers

The following example shows how the `Stack` API can be used with integer items:

```c
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

    int status, i;
    int val[] = {1, 2, 3};

    for (i = 0; i < 3; i++) {
        status = stack->push(stack, &val[i]);
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
```

## Usage example with user-defined data structures

Since the `Stack` implementation is generic, it is possible to handle user-defined data structures in the same way. The following example illustrates a stack accepting `struct` items:

```c
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
    status = stack->push(stack, &p2);
    status = stack->push(stack, &p3);
    printf("Status: %2d | Item(s): %d | Empty? %d | ",
            status, stack->size, stack->is_empty(stack));
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
```

## Tests

Running the tests provided in [`stack-test.c`](https://github.com/alexandra-zaharia/cdslib/blob/master/Stack/stack-test.c) requires [cmocka](https://cmocka.org). Build the tests with:

```bash
gcc -Wall stack-test.c stack.c -g -o stack-test -lcmocka
```
