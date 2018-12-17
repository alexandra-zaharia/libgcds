//
// Created by Alexandra Zaharia on 17/12/18.
//

#include <stdlib.h>
#include "queue.h"

// Creates and returns a Node* storing the designated data, or NULL in case of failure.
Node* node_create(void* data)
{
    Node* node = malloc(sizeof(Node));
    if (!node) return NULL;
    node->data = data;
    node->next = NULL;
    return node;
}

// Frees the queue.
void queue_free(Queue* queue)
{
    if (!queue) return;

    if (queue->first) {
        Node* node = queue->first;
        while (node) {
            Node* tmp = node;
            node = node->next;
            free(tmp);
        }
    }

    free(queue);
}

// Returns true if the queue is empty, false otherwise.
bool queue_is_empty(Queue* queue)
{
    return queue->first == NULL;
}

// Adds the item to the queue. Returns 0 for success and -1 for failure.
int queue_enqueue(Queue* queue, void* data)
{
    if (!queue) return -1;

    Node* node = node_create(data);
    if (!node) return -1;

    if (queue->is_empty(queue)) {
        queue->first = queue->last = node;
    } else {
        queue->last->next = node;
        queue->last = node;
    }

    ++queue->size;

    return 0;
}

// Removes and returns the least recently added node from the queue, or NULL in case of failure.
void* queue_dequeue(Queue* queue)
{
    if (!queue || !queue->first) return NULL;

    Node* node = queue->first;

    if (--queue->size == 0) {
        queue->first = queue->last = NULL;
    } else {
        queue->first = node->next;
        node->next = NULL;
    }

    void* data = node->data;
    free(node);

    return data;
}

// Creates and returns a Queue*, or NULL in case of failure.
Queue* queue_create()
{
    Queue* queue = malloc(sizeof(Queue));
    if (!queue) return NULL;

    queue->first = NULL;
    queue->last = NULL;
    queue->size = 0;

    queue->free = queue_free;
    queue->is_empty = queue_is_empty;

    queue->enqueue = queue_enqueue;
    queue->dequeue = queue_dequeue;

    return queue;
}
