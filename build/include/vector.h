#ifndef LIBGCDS_VECTOR_H
#define LIBGCDS_VECTOR_H

#include <stdbool.h>

typedef struct Vector Vector;

struct Vector {
    void** data;           // information stored in the vector
    unsigned int size;     // number of elements currently stored in the vector
    unsigned int capacity; // maximum capacity of the vector

    void (*free)(Vector*);                       // frees the vector

    int (*add)(Vector*, void*);                  // adds an item to the vector
    int (*insert)(Vector*, void*, unsigned int); // adds an item at a specified position
    void* (*remove)(Vector*, unsigned int);      // removes an item at a specified position

    bool (*contains)(Vector*, void*);            // does the vector contain a given item?
};

extern const unsigned int VECTOR_INIT_CAPACITY;

Vector* vector_create();

#endif //LIBGCDS_VECTOR_H
