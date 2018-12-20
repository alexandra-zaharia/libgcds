//
// Created by Alexandra Zaharia on 18/12/18.
//

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>
#include <stdlib.h>
#include "queue.h"

// Fixtures --------------------------------------------------------------------

/* Fixture setup: creates a Queue. */
static int setup_queue(void **state)
{
    Queue* queue = queue_create();
    assert_non_null(queue);
    *state = queue;
    return 0;
}

/* Fixture teardown: frees a Queue. */
static int teardown_queue(void **state)
{
    Queue* queue = (Queue*) *state;
    queue->free(queue);
    return 0;
}

int values[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

// Tests -----------------------------------------------------------------------

// Tests queue creation
static void test_queue_create(void **state)
{
    Queue* queue = (Queue*) *state;
    assert_non_null(queue);
    *state = queue;
}

// Tests whether the queue is empty upon creation
static void test_queue_is_empty(void **state)
{
    Queue* queue = (Queue*) *state;
    assert_true(queue->is_empty(queue));
    *state = queue;
}

// Tests insertion in the queue
static void test_queue_enqueue(void **state)
{
    Queue* queue = (Queue*) *state;

    for (int i = 0; i < 10; i++) {
        assert_int_equal(queue->enqueue(queue, &values[i]), 0);
        assert_int_equal(queue->size, i+1);
        assert_false(queue->is_empty(queue));
    }

    assert_int_equal(queue->enqueue(NULL, &values[0]), -1);
    assert_int_equal(queue->size, 10);
    assert_false(queue->is_empty(queue));

    *state = queue;
}

// Tests removal from the queue
static void test_queue_dequeue(void **state)
{
    Queue* queue = (Queue*) *state;

    for (int i = 0; i < 10; i++) {
        int val = *((int*) queue->dequeue(queue));
        assert_int_equal(val, values[i]);
        assert_int_equal(queue->size, 9 - i);
        i < 9 ? assert_false(queue->is_empty(queue)) : assert_true(queue->is_empty(queue));
    }

    int* val = (int*) queue->dequeue(queue);
    assert_null(val);
    assert_int_equal(queue->size, 0);
    assert_true(queue->is_empty(queue));

    *state = queue;
}

// Main ------------------------------------------------------------------------

int main()
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_queue_create),
            cmocka_unit_test(test_queue_is_empty),
            cmocka_unit_test(test_queue_enqueue),
            cmocka_unit_test(test_queue_dequeue)
    };

    return cmocka_run_group_tests(tests, setup_queue, teardown_queue);
}