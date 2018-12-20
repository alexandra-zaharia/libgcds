//
// Created by Alexandra Zaharia on 20/12/18.
//

#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

void vector_int_print(Vector *vector);

int main(void)
{
    unsigned int i;
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
    for (unsigned int i = 0; i < vector->count; i++)
        printf("%d ", *((int *) vector->data[i]));
    printf("]\n");
}
