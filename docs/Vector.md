# Generic vector implementation

This is a generic vector implementation using an underlying resizing array. A vector has an initial `capacity` of 4 elements. When the capacity is reached and a new item needs to be added, the vector doubles its capacity. The underlying array shrinks by half when the vector is 75% empty. For example, when adding the 5th item to a vector, its capacity goes from 4 to 8. If items are then removed from the vector, it goes back to a capacity of 4 when only two items remain. 

## API

The `Vector` API is detailed below.

**Fields:**
  * `void** data` -- information stored in the vector 
  * `unsigned int size` -- number of elements currently stored in the vector
  * `unsigned int capacity` -- maximum capacity of the vector

**Methods** (assume `vector` is a `Vector*`)**:**
  * `Vector* vector_create()` -- Creates a new `vector` and returns a pointer to it, or `NULL` in case of failure.
  * `vector->free(Vector* vector)` -- Frees the given `vector`.
  * `vector->add(Vector* vector, void* item)` -- Adds the `item` at the end of the `vector`, resizing the underlying array if necessary. Returns 0 on success and -1 on failure.
  * `vector->insert(Vector* vector, void* item, int index)` -- Inserts the `item` to the `vector` at the specified `index`, resizing the underlying array if necessary. Returns 0 on success and -1 on failure.
  * `vector->remove(Vector* vector, int index)` -- Deletes an item in the `vector` at the specified `index`, resizing the underlying array if necessary. Returns the item that was removed as a `void*`, or `NULL` in case of failure.
  * `vector->contains(Vector* vector, void* item)` -- Returns `true` if the vector contains the specified item, and `false` otherwise.
  * `vector->index(Vector* vector, void* item)` -- Returns the index of `item` in the `vector`, or -1 if the item is not found.

For more details:
  * [Vector header file](https://github.com/alexandra-zaharia/libgcds/blob/master/include/Vector/vector.h)
  * [Vecotr implementation](https://github.com/alexandra-zaharia/libgcds/blob/master/src/Vector/vector.c)