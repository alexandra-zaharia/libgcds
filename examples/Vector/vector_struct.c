//
// Created by Alexandra Zaharia on 20/12/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void vector_point_print(Vector* vector);

typedef struct {
    int x;
    int y;
} Point;

int main(void)
{
    Vector* vector = vector_create();
    if (!vector) {
        fprintf(stderr, "Cannot allocate vector.\n");
        exit(EXIT_FAILURE);
    }

    Point p1 = {.x = 1, .y = 10};
    Point p2 = {.x = 2, .y = 20};
    Point p3 = {.x = 3, .y = 30};

    vector->add(vector, &p1);
    vector->add(vector, &p3);
    vector->insert(vector, &p2, 1);

    vector_point_print(vector); /* [ (1, 10) (2, 20) (3, 30) ] */
    vector->free(vector);

    return EXIT_SUCCESS;
}

void vector_point_print(Vector* vector)
{
    printf("[ ");
    for (unsigned int i = 0; i < vector->size; i++) {
        Point* point = (Point*) vector->data[i];
        printf("(%d, %d) ", point->x, point->y);
    }
    printf("]\n");
}