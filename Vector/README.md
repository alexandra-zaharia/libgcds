# Generic vector implementation

This is a generic vector implementation using an underlying resizing array. A vector has an initial capacity of 4 elements. When the capacity is reached and a new item needs to be added, the vector doubles its capacity. The underlying array shrinks by half when the vector is 75% empty. For example, when adding the 5th item to a vector, its capacity goes from 4 to 8. If items are then removed from the vector, it goes back to a capacity of 4 when only two items remain.

## Data structure

A `Vector` is defined as follows:

```
typedef struct {
    void **data;     /* information stored in the vector */
    size_t count;    /* number of elements currently used in the vector */
    size_t capacity; /* maximum capacity of the vector */
} Vector;
```

## API

`Vector` has the following API:
* `Vector *vector_create()` -- Creates a new `vector` and returns a pointer to it, or `NULL` in case of failure.
* `void vector_free(Vector *vector)` -- Frees the given `vector`.
* `int vector_add(Vector *vector, void *item)` -- Adds the `item` at the end of the `vector`, resizing the underlying array if necessary. Returns 0 on success and -1 on failure.
* `int vector_insert(Vector *vector, void *item, int index)` -- Inserts the `item` to the `vector` at the specified `index`, resizing the underlying array if necessary. Returns 0 on success and -1 on failure.
* `int vector_delete(Vector *vector, int index)` -- Deletes an item in the `vector` at the specified `index`, resizing the underlying array if necessary. Returns 0 on success and -1 on failure.

## Usage example with integers

The following example shows how the `Vector` API can be used to add, insert or delete integer items:

```
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

void vector_int_print(Vector *vector);

int main(void)
{
    int i;
    Vector *vector = vector_create();
    if (!vector) {
        fprintf(stderr, "Cannot allocate vector.\n");
        exit(EXIT_FAILURE);
    }

    int even[3] = {2, 4, 6};
    for (i = 0; i < 3; i++)
        vector_add(vector, &even[i]);
    vector_int_print(vector); /* [ 2 4 6 ] */

    int odd[3] = {1, 3, 5};
    vector_insert(vector, &odd[0], 0);
    vector_insert(vector, &odd[1], 2);
    vector_insert(vector, &odd[2], 4);
    vector_int_print(vector); /* [ 1 2 3 4 5 6 ] */

    for (i = 5; i > 2; i--)
        vector_delete(vector, i);
    vector_int_print(vector); /* [ 1 2 3 ] */

    vector_free(vector);

    return EXIT_SUCCESS;
}

void vector_int_print(Vector *vector)
{
    printf("[ ");
    for (size_t i = 0; i < vector->count; i++)
        printf("%d ", *((int *) vector->data[i]));
    printf("]\n");
}
```

## Usage example with user-defined data structures

Since the `Vector` implementation is generic, it is possible to handle user-defined data structures in the same way. The following example illustrates adding and inserting `struct` items:

```
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

void vector_point_print(Vector *vector);

typedef struct {
    int x;
    int y;
} Point;

int main(void)
{
    Vector *vector = vector_create();
    if (!vector) {
        fprintf(stderr, "Cannot allocate vector.\n");
        exit(EXIT_FAILURE);
    }

    Point p1 = {.x = 1, .y = 10};
    Point p2 = {.x = 2, .y = 20};
    Point p3 = {.x = 3, .y = 30};
       
    vector_add(vector, &p1);
    vector_add(vector, &p3);
    vector_insert(vector, &p2, 1);

    vector_point_print(vector); /* [ (1, 10) (2, 20) (3, 30) ] */
    vector_free(vector);

    return EXIT_SUCCESS;
}

void vector_point_print(Vector *vector)
{
    printf("[ ");
    for (size_t i = 0; i < vector->count; i++) {
        Point *point = (Point *) vector->data[i];
        printf("(%d, %d) ", point->x, point->y);
    }
    printf("]\n");
}
```


## Tests

Running the tests provided in [`vector-test.c`](https://github.com/alexandra-zaharia/cdslib/blob/master/vector/vector-test.c) requires [cmocka](https://cmocka.org). Build the tests with:

```
gcc -Wall vector-test.c vector.c -g -o vector-test -lcmocka
```
