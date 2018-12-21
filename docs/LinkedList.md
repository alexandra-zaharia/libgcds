# Generic doubly linked list implementation

This is a generic doubly linked list implementation. In a doubly linked list, each node has a `next` and a `prev` pointer, designating the next and previous nodes, respectively. There is a `Node` pointer for the beginning of the list (`head`) and another one for the end of the list (`tail`). They correspond to the only node in the list with a null `prev` pointer and with a null `next` pointer, respectively. Additionally, it should be possible to know the `size` of a doubly linked list and whether it `is_empty`. 

## API

The `LinkedList` API is detailed below.

Fields:
  * [`DNode*`](https://github.com/alexandra-zaharia/libgcds/blob/master/include/node.h) `head` -- first node of the linked list
  * [`DNode*`](https://github.com/alexandra-zaharia/libgcds/blob/master/include/node.h) `tail` -- last node of the linked list
  * `unsigned int size` -- number of items in the linked list

Methods (assume `list` is a `LinkedList*`):
  * `LinkedList* linked_list_create()` -- Creates a new `LinkedList` and returns a pointer to it, or `NULL` in case of failure.
  * `list->free(LinkedList* list)` -- Frees the given linked `list`.
  * `list->is_empty(LinkedList* list)` -- Returns `true` if the linked `list` is empty, `false` otherwise.
  * `list->insert_start(LinkedList* list, void* data)` -- Adds the designated `data` at the beginning of the linked `list`. Returns 0 on success and -1 on failure.
  * `list->insert_end(LinkedList* list, void* data)` -- Adds the designated `data` at the end of the linked `list`. Returns 0 on success and -1 on failure.
  * `list->insert_at(LinkedList* list, void* data, unsigned int index)` -- Adds the designated `data` at the specified `index` of the linked `list`. Returns 0 on success and -1 on failure.
  * `list->remove_start(LinkedList* list)` -- Removes and returns the item at the beginning of the linked `list` as a `void*`. Returns `NULL` if the list is null or empty.
  * `list->remove_end(LinkedList* list)` -- Removes and returns the item at the end of the linked `list` as a `void*`. Returns `NULL` if the list is null or empty.
  * `list->remove_at(LinkedList* list, unsigned int index)` -- Removes and returns the item at the specified `index` of the linked `list` as a `void*`. Returns `NULL` if the list is null or empty, or if there is no item at the specified position.

For more details:
  * [Header file](https://github.com/alexandra-zaharia/libgcds/blob/master/include/LinkedList/linked_list.h)
  * [Implementation](https://github.com/alexandra-zaharia/libgcds/blob/master/src/LinkedList/linked_list.c)