# Generic doubly linked list implementation

This is a generic doubly linked list implementation. In a doubly linked list, each node has a `next` and a `prev` pointer, designating the next and previous nodes, respectively. There is a `Node` pointer for the beginning of the list (`head`) and another one for the end of the list (`tail`). They correspond to the only node in the list with a null `prev` pointer and with a null `next` pointer, respectively. Additionally, it should be possible to know the `size` of a doubly linked list and whether it `is_empty`. 

## API

`LinkedList` has the following API:
  * `LinkedList* linked_list_create()` -- Creates a new `LinkedList` and returns a pointer to it, or `NULL` in case of failure.
  * `list->free(list)` -- Frees the given linked `list`.
  * `list->is_empty(list)` -- Returns `true` if the linked `list` is empty, `false` otherwise.
  * `list->insert_start(list, data)` -- Adds the designated `data` at the beginning of the linked `list`. Returns 0 on success and -1 on failure.
  * `list->insert_end(list, data)` -- Adds the designated `data` at the end of the linked `list`. Returns 0 on success and -1 on failure.
  * `list->insert_at(list, data, index)` -- Adds the designated `data` at the specified `index` of the linked `list`. Returns 0 on success and -1 on failure.
  * `list->remove_start(list)` -- Removes and returns the item at the beginning of the linked `list`. Returns `NULL` if the list is null or empty.
  * `list->remove_end(list)` -- Removes and returns the item at the end of the linked `list`. Returns `NULL` if the list is null or empty.
  * `list->remove_at(list, index)` -- Removes and returns the item at the specified `index` of the linked `list`. Returns `NULL` if the list is null or empty, or if there is no item at the specified position.

## Usage example with integers

The following example shows how the `LinkedList` API can be used with integer items:

```c
#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

void print(LinkedList* list);

int main()
{
    LinkedList* list = linked_list_create();
    if (!list) {
        fprintf(stderr, "Cannot allocate linked list.\n");
        exit(EXIT_FAILURE);
    }

    int status, i;
    int val[] = {1, 2, 3};

    for (i = 0; i < 3; i++) {
        status = list->insert_end(list, &val[i]);
        printf("Status: %2d | Item(s): %d | Empty? %d | ",
                status, list->size, list->is_empty(list));
        print(list);
    }
    for (i = 0; i < 3; i++) {
        int value = *((int*) list->remove_start(list));
        printf("Value: %d | Item(s): %d | Empty? %d | ",
                value, list->size, list->is_empty(list));
        print(list);
    }

    list->free(list);
}

void print(LinkedList* list)
{
    if (!list || list->is_empty(list)) return;
    Node* node = list->head;
    while (node) {
        printf("%d ", *((int*) node->data));
        node = node->next;
    }
    printf("\n");
}
```

## Usage example with user-defined data structures

Since the `LinkedList` implementation is generic, it is possible to handle user-defined data structures in the same way. The following example illustrates a linked list accepting `struct` items:

```c
#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

void list_point_print(LinkedList* list);

typedef struct {
    int x;
    int y;
} Point;

int main()
{
    LinkedList* list = linked_list_create();
    if (!list) {
        fprintf(stderr, "Cannot allocate linked list.\n");
        exit(EXIT_FAILURE);
    }

    Point p1 = {.x = 1, .y = 10};
    Point p2 = {.x = 2, .y = 20};
    Point p3 = {.x = 3, .y = 30};
    int status;

    status = list->insert_end(list, &p1);
    status = list->insert_end(list, &p2);
    status = list->insert_end(list, &p3);
    printf("Status: %2d | Item(s): %d | Empty? %d | ",
           status, list->size, list->is_empty(list));
    list_point_print(list);

    for (int i = 0; i < 3; i++) {
        Point* p = (Point*) list->remove_start(list);
        printf("Popped: (%d, %d) | Item(s): %d | Empty? %d ",
               p->x, p->y, list->size, list->is_empty(list));
        list_point_print(list);
    }

    list->free(list);
}

void list_point_print(LinkedList* list)
{
    if (!list || list->is_empty(list)) return;
    Node* node = list->head;
    while (node) {
        Point* p = (Point*) node->data;
        printf("(%d, %d) ", p->x, p->y);
        node = node->next;
    }
    printf("\n");
}
```

## Tests

Running the tests provided in [`linked_list-test.c`](https://github.com/alexandra-zaharia/cdslib/blob/master/LinkedList/linked_list-test.c) requires [cmocka](https://cmocka.org). Build the tests with:

```bash
gcc -Wall linked_list-test.c linked_list.c -g -o linked_list-test -lcmocka
```
