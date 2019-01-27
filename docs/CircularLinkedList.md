# Generic circular doubly linked list implementation

This is a generic circular doubly linked list implementation. In a doubly linked list, each node has a `next` and a `prev` pointer, designating the next and previous nodes, respectively. There is a `Node` pointer for the beginning of the list (`head`) and another one for the end of the list (`tail`). Unlike a [doubly linked list](https://github.com/alexandra-zaharia/libgcds/blob/master/docs/LinkedList.md), in a circular doubly linked list the previous node of the `head` node is the `tail` node, and the next node with respect to the `tail` node is the `head` node. Additionally, it should be possible to know the `size` of a circular doubly linked list and whether it `is_empty`. 

## API

The `CircularLinkedList` API is detailed below.

**Fields:**
  * [`DNode*`](https://github.com/alexandra-zaharia/libgcds/blob/master/include/node.h) `head` -- first node of the circular linked list
  * [`DNode*`](https://github.com/alexandra-zaharia/libgcds/blob/master/include/node.h) `tail` -- last node of the circular linked list
  * `unsigned int size` -- number of items in the circular linked list

**Methods** (assume `list` is a `CircularLinkedList*`)**:**
  * `CircularLinkedList* circular_linked_list_create()` -- Creates a new `CircularLinkedList` and returns a pointer to it, or `NULL` in case of failure.
  * `list->free(CircularLinkedList* list)` -- Frees the given circular linked `list`.
  * `list->is_empty(CircularLinkedList* list)` -- Returns `true` if the circular linked `list` is empty, `false` otherwise.
  * `list->insert_start(CircularLinkedList* list, void* data)` -- Adds the designated `data` at the beginning of the circular linked `list`. Returns 0 on success and -1 on failure.
  * `list->insert_end(CircularLinkedList* list, void* data)` -- Adds the designated `data` at the end of the circular linked `list`. Returns 0 on success and -1 on failure.
  * `list->insert_at(CircularLinkedList* list, void* data, int index)` -- Adds the designated `data` at the specified `index` of the circular linked `list`. Returns 0 on success and -1 on failure.
  * `list->remove_start(CircularLinkedList* list)` -- Removes and returns the item at the beginning of the circular linked `list` as a `void*`. Returns `NULL` if the list is null or empty.
  * `list->remove_end(CircularLinkedList* list)` -- Removes and returns the item at the end of the circular linked `list` as a `void*`. Returns `NULL` if the list is null or empty.
  * `list->remove_at(CircularLinkedList* list, int index)` -- Removes and returns the item at the specified `index` of the circular linked `list` as a `void*`. Returns `NULL` if the list is null or empty, or if there is no item at the specified position.
  * `list->contains(CircularLinkedList* list, void* item)` -- Returns `true` if the circular linked list contains the item, and `false` otherwise.

For more details:
  * [Circular linked list header file](https://github.com/alexandra-zaharia/libgcds/blob/master/include/CircularLinkedList/circular_linked_list.h)
  * [Circular linked list implementation](https://github.com/alexandra-zaharia/libgcds/blob/master/src/CircularLinkedList/circular_linked_list.c)
