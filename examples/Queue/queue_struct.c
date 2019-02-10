//
// Created by Alexandra Zaharia on 20/12/18.
//

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

void queue_point_print(Queue* queue);

typedef struct {
    int x;
    int y;
} Point;

int main()
{
    Queue* queue = queue_create();
    if (!queue) {
        fprintf(stderr, "Cannot allocate queue.\n");
        exit(EXIT_FAILURE);
    }

    Point p1 = {.x = 1, .y = 10};
    Point p2 = {.x = 2, .y = 20};
    Point p3 = {.x = 3, .y = 30};

    int status;
    status = queue->enqueue(queue, &p1);
    printf("Status: %2d | Item(s): %d | Empty? %d | ", status, queue->size, queue->is_empty(queue));
    queue_point_print(queue);
    status = queue->enqueue(queue, &p2);
    printf("Status: %2d | Item(s): %d | Empty? %d | ", status, queue->size, queue->is_empty(queue));
    queue_point_print(queue);
    status = queue->enqueue(queue, &p3);
    printf("Status: %2d | Item(s): %d | Empty? %d | ", status, queue->size, queue->is_empty(queue));
    queue_point_print(queue);

    for (int i = 0; i < 3; i++) {
        Point* p = (Point*) queue->dequeue(queue);
        printf("Popped: (%d, %d) | Item(s): %d | Empty? %d ",
               p->x, p->y, queue->size, queue->is_empty(queue));
        queue_point_print(queue);
    }

    queue->free(queue);
}

void queue_point_print(Queue* queue)
{
    if (!queue || !queue->first) return;
    Node* item = queue->first;
    while (item) {
        Point* p = (Point*) item->data;
        printf("(%d, %d) ", p->x, p->y);
        item = item->next;
    }
    printf("\n");
}