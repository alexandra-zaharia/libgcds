#include "vector.h"

const size_t VECTOR_INIT_CAPACITY = 4;

/* Creates and returns a pointer to Vector. If the Vector cannot be allocated,
 * a NULL pointer is returned. */
Vector *vector_create()
{
    Vector *vector = (Vector *)malloc(sizeof(Vector));
    if (!vector) return NULL;

    vector->count = 0;
    vector->capacity = VECTOR_INIT_CAPACITY;

    vector->data = (void *)malloc(vector->capacity * sizeof(void *));
    if (!vector->data) {
        vector_free(vector);
        return NULL;
    }

    return vector;
}

/* Frees the given Vector, if not NULL. */
void vector_free(Vector *vector)
{
    if (vector) {
        if (vector->data)
            free(vector->data);
        free(vector);
    }
}

/* Resizes the Vector to the specified capacity. Returns 0 on success and -1 on
 * failure. */
static int _vector_resize(Vector *vector, size_t capacity)
{
    void **data = realloc(vector->data, capacity * sizeof(void *));
    vector->capacity = capacity;

    if (!data) return -1;
    if (data != vector->data)
        vector->data = data;
    data = NULL;

    return 0;
}

/* Adds an item at the end of the Vector. Returns 0 on success and -1 on
 * failure. */
int vector_add(Vector *vector, void *item)
{
    if (!vector || !vector->data) return -1;

    if (vector->count == vector->capacity) {
        if (_vector_resize(vector, 2 * vector->capacity) == -1)
            return -1;
    }

    vector->data[vector->count++] = item;

    return 0;
}

/* Inserts an item at a specified index in the Vector. Returns 0 on success and
 * -1 on failure. */
int vector_insert(Vector *vector, void *item, int index)
{
    if (!vector || !vector->data) return -1;
    if (index < 0 || index > vector->count) return -1;

    if (index == vector->count) {
        if (vector_add(vector, item) == -1) return -1;
    } else {
        if (vector->count == vector->capacity) {
            if (_vector_resize(vector, 2 * vector->capacity) == -1)
                return -1;
        }

        for (int i = vector->count; i > index; i--)
            vector->data[i] = vector->data[i-1];

        vector->data[index] = item;
        vector->count++;
    }

    return 0;
}

/* Deletes the item at the specified index in the Vector. Returns 0 on success
 * and -1 on failure. */
int vector_delete(Vector *vector, int index)
{
    if (!vector || !vector->data) return -1;
    if (index < 0 || index >= vector->count) return -1;

    vector->count--;

    for (int i = index; i < vector->count; i++)
        vector->data[i] = vector->data[i+1];

    if (vector->count == vector->capacity / 4
            && vector->capacity > VECTOR_INIT_CAPACITY) {
        if (_vector_resize(vector, vector->capacity / 2) == -1)
            return -1;
    }

    return 0;
}
