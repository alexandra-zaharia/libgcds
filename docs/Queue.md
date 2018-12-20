# Generic queue implementation

This is a generic queue implementation. A queue is a FIFO (first in, first out) data structure that supports two main operations: adding data to the queue (`enqueue`) and retrieving the least recently added item (`dequeue`). Additionally, it should be possible to know the `size` of a queue and whether it `is_empty`. 

## API

`Queue` has the following API:
  * `Queue* queue_create()` -- Creates a new `Queue` and returns a pointer to it, or `NULL` in case of failure.
  * `queue->free(queue)` -- Frees the given `queue`.
  * `queueu->is_empty(queue)` -- Returns `true` if the `queue` is empty, `false` otherwise.
  * `queue->enqueue(queue, item)` -- Adds the `item` to the `queue`. Returns 0 on success and -1 on failure.
  * `queue->dequeue(queue)` -- Removes and returns the least recently added item of the `queue`. Returns `NULL` if the queue is null or empty.

## Usage example with integers

The following example shows how the `Queue` API can be used with integer items:

```c
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

void print(Queue* queue);

int main()
{
    Queue* queue = queue_create();
    if (!queue) {
        fprintf(stderr, "Cannot allocate queue.\n");
        exit(EXIT_FAILURE);
    }

    int status, i;
    int val[] = {1, 2, 3};

    for (i = 0; i < 3; i++) {
        status = queue->enqueue(queue, &val[i]);
        printf("Status: %2d | Item(s): %d | Empty? %d | ",
               status, queue->size, queue->is_empty(queue));
        print(queue);
    }
    for (i = 0; i < 3; i++) {
        int value = *((int*) queue->dequeue(queue));
        printf("Value: %d | Item(s): %d | Empty? %d | ",
               value, queue->size, queue->is_empty(queue));
        print(queue);
    }

    queue->free(queue);
}

void print(Queue* queue)
{
    if (!queue|| !queue->first) return;
    Node* node = queue->first;
    while (node) {
        printf("%d ", *((int*) node->data));
        node = node->next;
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

Running the tests provided in [`queue-test.c`](https://github.com/alexandra-zaharia/cdslib/blob/master/Queue/queue-test.c) requires [cmocka](https://cmocka.org). Build the tests with:

```bash
gcc -Wall queue-test.c queue.c ../node.c -g -o queue-test -lcmocka
```
