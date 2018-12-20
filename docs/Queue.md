# Generic queue implementation

This is a generic queue implementation. A queue is a FIFO (first in, first out) data structure that supports two main operations: adding data to the queue (`enqueue`) and retrieving the least recently added item (`dequeue`). Additionally, it should be possible to know the `size` of a queue and whether it `is_empty`. 

`Queue` has the following API:
  * `Queue* queue_create()` -- Creates a new `Queue` and returns a pointer to it, or `NULL` in case of failure.
  * `queue->free(queue)` -- Frees the given `queue`.
  * `queueu->is_empty(queue)` -- Returns `true` if the `queue` is empty, `false` otherwise.
  * `queue->enqueue(queue, item)` -- Adds the `item` to the `queue`. Returns 0 on success and -1 on failure.
  * `queue->dequeue(queue)` -- Removes and returns the least recently added item of the `queue`. Returns `NULL` if the queue is null or empty.

For more details:
  * [header file](https://github.com/alexandra-zaharia/libgcds/blob/master/include/Queue/queue.h)
  * [implementation](https://github.com/alexandra-zaharia/libgcds/blob/master/src/Queue/queue.c)