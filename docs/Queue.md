# Generic queue implementation

This is a generic queue implementation. A queue is a FIFO (first in, first out) data structure that supports two main operations: adding data to the queue (`enqueue`) and retrieving the least recently added item (`dequeue`). Additionally, it should be possible to know the `size` of a queue and whether it `is_empty`. 

## API
The `Queue` API is detailed below.

**Fields:**
  * [`Node*`](https://github.com/alexandra-zaharia/libgcds/blob/master/include/node.h) `first` -- the least recently added node
  * [`Node*`](https://github.com/alexandra-zaharia/libgcds/blob/master/include/node.h) `last` -- the most recently added node
  * `unsigned int size` -- number of items in the queue
  
**Methods** (assume `queue` is a `Queue*`)**:**
  * `Queue* queue_create()` -- Creates a new `Queue` and returns a pointer to it, or `NULL` in case of failure.
  * `queue->free(Queue* queue)` -- Frees the given `queue`.
  * `queue->is_empty(Queue* queue)` -- Returns `true` if the `queue` is empty, `false` otherwise.
  * `queue->enqueue(Queue* queue, void* data)` -- Adds the `data` to the `queue`. Returns 0 on success and -1 on failure.
  * `queue->dequeue(Queue* queue)` -- Removes and returns the least recently added item of the `queue`. Returns `NULL` if the queue is null or empty.

For more details:
  * [Queue header file](https://github.com/alexandra-zaharia/libgcds/blob/master/include/Queue/queue.h)
  * [Queue implementation](https://github.com/alexandra-zaharia/libgcds/blob/master/src/Queue/queue.c)