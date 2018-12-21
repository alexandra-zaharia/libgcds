# Generic stack implementation

This is a generic stack implementation. A stack is a LIFO (last in, first out) data structure that supports two main operations: adding data on top of the stack (`push`) and retrieving the topmost item on the stack (`pop`). Additionally, it should be possible to know a `size` of a stack and whether it `is_empty`. 

## API

The `Stack` API is detailed below.

Fields:
  * [`Item*`](https://github.com/alexandra-zaharia/libgcds/blob/master/include/node.h) `top` -- the first (top) item in the stack
  * `unsigned int size` -- number of items in the stack
  
Methods (assume `stack` is a `Stack*`):
  * `Stack* stack_create()` -- Creates a new `Stack` and returns a pointer to it, or `NULL` in case of failure.
  * `stack->free(Stack* stack)` -- Frees the given `stack`.
  * `stack->is_empty(Stack* stack)` -- Returns `true` if the `stack` is empty, `false` otherwise.
  * `stack->push(Stack* stack, void* data)` -- Adds the `data` on top of the `stack`. Returns 0 on success and -1 on failure.
  * `stack->pop(Stack* stack)` -- Removes and returns the item on top of the `stack`. Returns `NULL` if the stack is null or empty.

For more details:
  * [Header file](https://github.com/alexandra-zaharia/libgcds/blob/master/include/Stack/stack.h)
  * [Implementation](https://github.com/alexandra-zaharia/libgcds/blob/master/src/Stack/stack.c)