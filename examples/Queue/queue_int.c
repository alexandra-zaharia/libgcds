//
// Created by Alexandra Zaharia on 20/12/18.
//

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

void print(Queue* queue);

int main()
{
    Queue* queue = queue_create();
    if (!queue) {
        fprintf(stderr, "Cannot allocate queue.\n");
        exit(EXIT_FAILURE);
    }

    int val[] = {1, 2, 3};
    int i;

    for (i = 0; i < 3; i++) {
        int status = queue->enqueue(queue, &val[i]);
        printf("Status: %2d | Item(s): %d | Empty? %d | ",
               status, queue->size, queue->is_empty(queue));
        print(queue);
    }
    for (i = 0; i < 3; i++) {
        int value = *((int*) queue->dequeue(queue));
        printf("Value: %d | Item(s): %d | Empty? %d | ",
               value, queue->size, queue->is_empty(queue));
        print(queue);
    }

    queue->free(queue);
}

void print(Queue* queue)
{
    if (!queue|| !queue->first) return;
    Node* node = queue->first;
    while (node) {
        printf("%d ", *((int*) node->data));
        node = node->next;
    }
    printf("\n");
}