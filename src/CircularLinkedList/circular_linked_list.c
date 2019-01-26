//
// Created by Alexandra Zaharia on 26/01/19.
//

#include <stdlib.h>
#include "circular_linked_list.h"

// Frees the circular linked list.
void circular_linked_list_free(CircularLinkedList* list)
{
    if (!list) return;

    while (list->head) {
        list->remove_start(list);
    }

    free(list);
}

// Returns true if the circular linked list is empty, false otherwise.
bool circular_linked_list_is_empty(CircularLinkedList* list)
{
    return list->head == NULL;
}

// Makes a doubly linked list circular.
void _circularize(CircularLinkedList* list)
{
    list->head->prev = list->tail;
    list->tail->next = list->head;
}

/*
 * Inserts the item at the front of the circular linked list. Returns 0 for success and -1 for
 * failure.
 */
int circular_linked_list_insert_start(CircularLinkedList* list, void* data)
{
    if (!list) return -1;

    DNode* node = dnode_create(data);
    if (!node) return -1;

    if (list->is_empty(list)) {
        list->head = list->tail = node;
    } else {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
        _circularize(list);
    }

    ++list->size;

    return 0;
}

/*
 * Inserts the item at the end of the circular linked list. Returns 0 for success and -1 for
 * failure.
 */
int circular_linked_list_insert_end(CircularLinkedList* list, void* data)
{
    if (!list) return -1;

    DNode* node = dnode_create(data);
    if (!node) return -1;

    if (list->is_empty(list)) {
        list->tail = list->head = node;
    } else {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
        _circularize(list);
    }

    ++list->size;

    return 0;
}

/*
 * Returns the DNode* at the designated index in the circular linked list, or NULL in case of
 * failure.
 */
static DNode* _find_node_at_index(CircularLinkedList* list, unsigned int index)
{
    if (!list || (int) index < 0 || index >= list->size) return NULL;

    DNode* node;
    unsigned int current_index;

    if (index <= list->size / 2) {
        node = list->head;
        current_index = 0;
        while (current_index < index) {
            node = node->next;
            ++current_index;
        }
    } else {
        node = list->tail;
        current_index = list->size - 1;
        while (current_index > index) {
            node = node->prev;
            --current_index;
        }
    }

    return node;
}

/*
 * Inserts the item at a designated position 'index' of the circular linked list. Returns 0 for
 * success and -1 for failure.
 */
int circular_linked_list_insert_at(CircularLinkedList* list, void* data, unsigned int index)
{
    if (!list || (int) index < 0 || index > list->size) return -1;
    if (index == 0) return list->insert_start(list, data);
    if (index == list->size) return list->insert_end(list, data);

    DNode* node = dnode_create(data);
    if (!node) return -1;
    DNode* node_at_index = _find_node_at_index(list, index);
    if (!node_at_index) return -1;

    node_at_index->prev->next = node;
    node->prev = node_at_index->prev;
    node_at_index->prev = node;
    node->next = node_at_index;

    ++list->size;

    return 0;
}

/*
 * Removes and returns the item at the front of the circular linked list, or NULL in case of
 * failure.
 */
void* circular_linked_list_remove_start(CircularLinkedList* list)
{
    if (!list || !list->head) return NULL;

    DNode* node = list->head;

    if (--list->size == 0) {
        list->head = list->tail = NULL;
    } else {
        node->next->prev = list->tail;
        list->head = node->next;
        list->tail->next = list->head;
    }

    void* data = node->data;
    free(node);

    return data;
}


// Removes and returns the item at the end of the circular linked list, or NULL in case of failure.
void* circular_linked_list_remove_end(CircularLinkedList* list)
{
    if (!list || !list->tail) return NULL;

    DNode* node = list->tail;

    if (--list->size == 0) {
        list->head = list->tail = NULL;
    } else {
        node->prev->next = list->head;
        list->tail = node->prev;
        list->head->prev = list->tail;
    }

    void* data = node->data;
    free(node);

    return data;
}

/*
 * Removes and returns the item at a designated position 'index' of the circular linked list, or
 * NULL in case of failure.
 */
void* circular_linked_list_remove_at(CircularLinkedList* list, unsigned int index)
{
    if (!list || (int) index < 0 || index >= list->size) return NULL;
    if (index == 0) return list->remove_start(list);
    if (index == list->size - 1) return list->remove_end(list);

    DNode* node = _find_node_at_index(list, index);
    if (!node) return NULL;

    node->prev->next = node->next;
    node->next->prev = node->prev;

    void* data = node->data;
    free(node);
    --list->size;

    return data;
}

// Creates and returns a CircularLinkedList*, or NULL in case of failure.
CircularLinkedList* circular_linked_list_create()
{
    CircularLinkedList* list = malloc(sizeof(CircularLinkedList));
    if (!list) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    list->free = circular_linked_list_free;
    list->is_empty = circular_linked_list_is_empty;

    list->insert_start = circular_linked_list_insert_start;
    list->insert_end = circular_linked_list_insert_end;
    list->insert_at = circular_linked_list_insert_at;

    list->remove_start = circular_linked_list_remove_start;
    list->remove_end = circular_linked_list_remove_end;
    list->remove_at = circular_linked_list_remove_at;

    return list;
}