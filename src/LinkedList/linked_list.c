//
// Created by Alexandra Zaharia on 13/12/18.
//

#include <stdlib.h>
#include "linked_list.h"

// Frees the linked list.
void linked_list_free(LinkedList* list)
{
    if (!list) return;

    if (list->head) {
        DNode* node = list->head;
        while (node) {
            DNode* tmp = node;
            node = node->next;
            free(tmp);
        }
    }

    free(list);
}

// Returns true if the linked list is empty, false otherwise.
bool linked_list_is_empty(LinkedList* list)
{
    return list->head == NULL;
}

// Inserts the item at the front of the linked list. Returns 0 for success and -1 for failure.
int linked_list_insert_start(LinkedList* list, void* data)
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
    }

    ++list->size;

    return 0;
}

// Inserts the item at the end of the linked list. Returns 0 for success and -1 for failure.
int linked_list_insert_end(LinkedList* list, void* data)
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
    }

    ++list->size;

    return 0;
}

// Returns the DNode* at the designated index in the linked list, or NULL in case of failure.
static DNode* _find_node_at_index(LinkedList* list, unsigned int index)
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
 * Inserts the item at a designated position 'index' of the linked list. Returns 0 for success and
 * -1 for failure.
 */
int linked_list_insert_at(LinkedList* list, void* data, unsigned int index)
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

 // Removes and returns the item at the front of the linked list, or NULL in case of failure.
void* linked_list_remove_start(LinkedList* list)
{
    if (!list || !list->head) return NULL;

    DNode* node = list->head;

    if (--list->size == 0) {
        list->head = list->tail = NULL;
    } else {
        node->next->prev = NULL;
        list->head = node->next;
    }

    void* data = node->data;
    free(node);

    return data;
}

// Removes and returns the item at the end of the linked list, or NULL in case of failure.
void* linked_list_remove_end(LinkedList* list)
{
    if (!list || !list->tail) return NULL;

    DNode* node = list->tail;

    if (--list->size == 0) {
        list->head = list->tail = NULL;
    } else {
        node->prev->next = NULL;
        list->tail = node->prev;
    }

    void* data = node->data;
    free(node);

    return data;
}

/*
 * Removes and returns the item at a designated position 'index' of the linked list, or NULL in case
 * of failure.
 */
void* linked_list_remove_at(LinkedList* list, unsigned int index)
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

// Creates and returns a LinkedList*, or NULL in case of failure.
LinkedList* linked_list_create()
{
    LinkedList* list = malloc(sizeof(LinkedList));
    if (!list) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    list->free = linked_list_free;
    list->is_empty = linked_list_is_empty;

    list->insert_start = linked_list_insert_start;
    list->insert_end = linked_list_insert_end;
    list->insert_at = linked_list_insert_at;

    list->remove_start = linked_list_remove_start;
    list->remove_end = linked_list_remove_end;
    list->remove_at = linked_list_remove_at;

    return list;
}
