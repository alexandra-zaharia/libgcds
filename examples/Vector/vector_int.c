//
// Created by Alexandra Zaharia on 20/12/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void vector_int_print(Vector* vector);

int main(void)
{
    unsigned int i;
    Vector* vector = vector_create();
    if (!vector) {
        fprintf(stderr, "Cannot allocate vector.\n");
        exit(EXIT_FAILURE);
    }

    int even[3] = {2, 4, 6};
    for (i = 0; i < 3; i++)
        vector->add(vector, &even[i]);
    vector_int_print(vector); /* [ 2 4 6 ] */

    int odd[3] = {1, 3, 5};
    vector->insert(vector, &odd[0], 0);
    vector->insert(vector, &odd[1], 2);
    vector->insert(vector, &odd[2], 4);
    vector_int_print(vector); /* [ 1 2 3 4 5 6 ] */

    for (i = 5; i > 2; i--)
        vector->remove(vector, i);
    vector_int_print(vector); /* [ 1 2 3 ] */

    vector->free(vector);

    return EXIT_SUCCESS;
}

void vector_int_print(Vector* vector)
{
    printf("[ ");
    for (unsigned int i = 0; i < vector->size; i++)
        printf("%d ", *((int *) vector->data[i]));
    printf("]\n");
}
