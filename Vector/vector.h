#ifndef CDSLIB_VECTOR_H
#define CDSLIB_VECTOR_H

#include <stdlib.h>

typedef struct {
    void **data;           /* information stored in the vector */
    unsigned int count;    /* number of elements currently used in the vector */
    unsigned int capacity; /* maximum capacity of the vector */
} Vector;

extern const unsigned int VECTOR_INIT_CAPACITY;

Vector *vector_create();
void vector_free(Vector *vector);

int vector_add(Vector *vector, void *item);
int vector_insert(Vector *vector, void *item, unsigned int index);
int vector_delete(Vector *vector, unsigned int index);


#endif // CDSLIB_VECTOR_H
