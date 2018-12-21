#include <stdlib.h>
#include "vector.h"

const unsigned int VECTOR_INIT_CAPACITY = 4;

// Frees the vector.
void vector_free(Vector* vector)
{
    if (vector) {
        if (vector->data)
            free(vector->data);
        free(vector);
    }
}

// Resizes the vector to the specified capacity. Returns 0 for success and -1 for failure.
static int _vector_resize(Vector* vector, unsigned int capacity)
{
    void** data = realloc(vector->data, capacity * sizeof(void*));
    vector->capacity = capacity;

    if (!data) return -1;
    if (data != vector->data)
        vector->data = data;

    return 0;
}

// Adds an item at the end of the vector. Returns 0 for success and -1 for failure.
int vector_add(Vector* vector, void* item)
{
    if (!vector || !vector->data) return -1;

    if (vector->size == vector->capacity) {
        if (_vector_resize(vector, 2 * vector->capacity) == -1)
            return -1;
    }

    vector->data[vector->size++] = item;

    return 0;
}

// Inserts an item at a specified index in the vector. Returns 0 for success and -1 for failure.
int vector_insert(Vector* vector, void* item, unsigned int index)
{
    if (!vector || !vector->data) return -1;
    if ((int) index < 0 || index > vector->size) return -1;

    if (index == vector->size) {
        if (vector_add(vector, item) == -1) return -1;
    } else {
        if (vector->size == vector->capacity) {
            if (_vector_resize(vector, 2 * vector->capacity) == -1)
                return -1;
        }

        for (size_t i = vector->size; i > index; i--)
            vector->data[i] = vector->data[i-1];

        vector->data[index] = item;
        ++vector->size;
    }

    return 0;
}

// Removes and returns the item at the specified index in the vector, or NULL in case of failure.
void* vector_remove(Vector* vector, unsigned int index)
{
    if (!vector || !vector->data) return NULL;
    if ((int) index < 0 || index >= vector->size) return NULL;

    --vector->size;

    void* data = vector->data[index];

    for (size_t i = index; i < vector->size; i++)
        vector->data[i] = vector->data[i+1];

    if (vector->size == vector->capacity / 4 && vector->capacity > VECTOR_INIT_CAPACITY) {
        if (_vector_resize(vector, vector->capacity / 2) == -1)
            return NULL;
    }

    return data;
}

// Creates and returns a pointer to Vector, or NULL in case of failure.
Vector* vector_create()
{
    Vector* vector = malloc(sizeof(Vector));
    if (!vector) return NULL;

    vector->size = 0;
    vector->capacity = VECTOR_INIT_CAPACITY;

    vector->data = malloc(vector->capacity * sizeof(void*));
    if (!vector->data) {
        vector_free(vector);
        return NULL;
    }

    vector->free = vector_free;

    vector->add = vector_add;
    vector->insert = vector_insert;
    vector->remove = vector_remove;

    return vector;
}
