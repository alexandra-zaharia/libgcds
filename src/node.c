//
// Created by Alexandra Zaharia on 18/12/18.
//

#include <stdlib.h>
#include "node.h"

// Creates and returns a Node* storing the designated data, or NULL in case of failure.
Node* node_create(void* data)
{
    Node* node = malloc(sizeof(Node));
    if (!node) return NULL;
    node->data = data;
    node->next = NULL;
    return node;
}

/*
 * Creates and returns a Node* storing the designated data, or NULL in case of failure. Assumes
 * Item is typedef-ed as Node.
 */
Item* item_create(void* data)
{
    return node_create(data);
}

// Creates and returns a DNode* storing the designated data, or NULL in case of failure.
DNode* dnode_create(void* data)
{
    DNode* node = malloc(sizeof(DNode));
    if (!node) return NULL;
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}
