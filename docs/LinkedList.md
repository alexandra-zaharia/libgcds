# Generic doubly linked list implementation

This is a generic doubly linked list implementation. In a doubly linked list, each node has a `next` and a `prev` pointer, designating the next and previous nodes, respectively. There is a `Node` pointer for the beginning of the list (`head`) and another one for the end of the list (`tail`). They correspond to the only node in the list with a null `prev` pointer and with a null `next` pointer, respectively. Additionally, it should be possible to know the `size` of a doubly linked list and whether it `is_empty`. 

`LinkedList` has the following API:
  * `LinkedList* linked_list_create()` -- Creates a new `LinkedList` and returns a pointer to it, or `NULL` in case of failure.
  * `list->free(list)` -- Frees the given linked `list`.
  * `list->is_empty(list)` -- Returns `true` if the linked `list` is empty, `false` otherwise.
  * `list->insert_start(list, data)` -- Adds the designated `data` at the beginning of the linked `list`. Returns 0 on success and -1 on failure.
  * `list->insert_end(list, data)` -- Adds the designated `data` at the end of the linked `list`. Returns 0 on success and -1 on failure.
  * `list->insert_at(list, data, index)` -- Adds the designated `data` at the specified `index` of the linked `list`. Returns 0 on success and -1 on failure.
  * `list->remove_start(list)` -- Removes and returns the item at the beginning of the linked `list`. Returns `NULL` if the list is null or empty.
  * `list->remove_end(list)` -- Removes and returns the item at the end of the linked `list`. Returns `NULL` if the list is null or empty.
  * `list->remove_at(list, index)` -- Removes and returns the item at the specified `index` of the linked `list`. Returns `NULL` if the list is null or empty, or if there is no item at the specified position.

For more details:
  * [header file](https://github.com/alexandra-zaharia/libgcds/blob/master/include/LinkedList/linked_list.h)
  * [implementation](https://github.com/alexandra-zaharia/libgcds/blob/master/src/LinkedList/linked_list.c)