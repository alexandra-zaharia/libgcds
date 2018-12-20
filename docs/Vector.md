# Generic vector implementation

This is a generic vector implementation using an underlying resizing array. A vector has an initial `capacity` of 4 elements. When the capacity is reached and a new item needs to be added, the vector doubles its capacity. The underlying array shrinks by half when the vector is 75% empty. For example, when adding the 5th item to a vector, its capacity goes from 4 to 8. If items are then removed from the vector, it goes back to a capacity of 4 when only two items remain. 

## Data structure

A `Vector` is defined as follows:

```c
typedef struct {
    void **data;           /* information stored in the vector */
    unsigned int count;    /* number of elements currently used in the vector */
    unsigned int capacity; /* maximum capacity of the vector */
} Vector;
```

## API

`Vector` has the following API:
  * `Vector *vector_create()` -- Creates a new `vector` and returns a pointer to it, or `NULL` in case of failure.
  * `void vector_free(Vector *vector)` -- Frees the given `vector`.
  * `int vector_add(Vector *vector, void *item)` -- Adds the `item` at the end of the `vector`, resizing the underlying array if necessary. Returns 0 on success and -1 on failure.
  * `int vector_insert(Vector *vector, void *item, unsigned int index)` -- Inserts the `item` to the `vector` at the specified `index`, resizing the underlying array if necessary. Returns 0 on success and -1 on failure.
  * `int vector_delete(Vector *vector, unsigned int index)` -- Deletes an item in the `vector` at the specified `index`, resizing the underlying array if necessary. Returns 0 on success and -1 on failure.

For more details:
  * [header file](https://github.com/alexandra-zaharia/libgcds/blob/master/include/Vector/vector.h)
  * [implementation](https://github.com/alexandra-zaharia/libgcds/blob/master/src/Vector/vector.c)