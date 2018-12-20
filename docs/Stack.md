# Generic stack implementation

This is a generic stack implementation. A stack is a LIFO (last in, first out) data structure that supports two main operations: adding data on top of the stack (`push`) and retrieving the topmost item on the stack (`pop`). Additionally, it should be possible to know a `size` of a stack and whether it `is_empty`. 

`Stack` has the following API:
  * `Stack* stack_create()` -- Creates a new `Stack` and returns a pointer to it, or `NULL` in case of failure.
  * `stack->free(stack)` -- Frees the given `stack`.
  * `stack->is_empty(stack)` -- Returns `true` if the `stack` is empty, `false` otherwise.
  * `stack->push(stack, item)` -- Adds the `item` on top of the `stack`. Returns 0 on success and -1 on failure.
  * `stack->pop(stack)` -- Removes and returns the item on top of the `stack`. Returns `NULL` if the stack is null or empty.

For more details:
  * [header file](https://github.com/alexandra-zaharia/libgcds/blob/master/include/Stack/stack.h)
  * [implementation](https://github.com/alexandra-zaharia/libgcds/blob/master/src/Stack/stack.c)