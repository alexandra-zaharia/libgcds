//
// Created by Alexandra Zaharia on 13/12/18.
//

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>
#include <stdlib.h>
#include "stack.h"

// Fixtures --------------------------------------------------------------------

/* Fixture setup: creates a Stack. */
static int setup_stack(void **state)
{
    Stack* stack = stack_create();
    assert_non_null(stack);
    *state = stack;
    return 0;
}

/* Fixture teardown: frees a Stack. */
static int teardown_stack(void **state)
{
    Stack* stack = (Stack*) *state;
    stack->free(stack);
    return 0;
}

int values[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

// Tests -----------------------------------------------------------------------

// Tests stack creation
static void test_stack_create(void **state)
{
    Stack* stack = (Stack*) *state;
    assert_non_null(stack);
    *state = stack;
}

// Tests whether the stack is empty upon creation
static void test_stack_is_empty(void **state)
{
    Stack* stack = (Stack*) *state;
    assert_true(stack->is_empty(stack));
    *state = stack;
}

// Tests insertion in the stack
static void test_stack_push(void **state)
{
    Stack* stack = (Stack*) *state;

    for (int i = 0; i < 10; i++) {
        assert_int_equal(stack->push(stack, &values[i]), 0);
        assert_int_equal(stack->size, i+1);
        assert_false(stack->is_empty(stack));
    }

    assert_int_equal(stack->push(NULL, &values[0]), -1);
    assert_int_equal(stack->size, 10);
    assert_false(stack->is_empty(stack));

    *state = stack;
}

// Tests removal from the stack
static void test_stack_pop(void **state)
{
    Stack* stack = (Stack*) *state;

    for (int i = 9; i >= 0; i--) {
        int val = *((int*) stack->pop(stack));
        assert_int_equal(val, values[i]);
        assert_int_equal(stack->size, i);
        i > 0 ? assert_false(stack->is_empty(stack)) : assert_true(stack->is_empty(stack));
    }

    int* val = (int*) stack->pop(stack);
    assert_null(val);
    assert_int_equal(stack->size, 0);
    assert_true(stack->is_empty(stack));

    *state = stack;
}

// Ensures that the 'contains' operation works as expected
static void test_stack_contains(void** state)
{
    Stack* stack = (Stack*) *state;

    for (int i = 0; i < 10; i++) {
        assert_int_equal(stack->push(stack, &values[i]), 0);
        assert_true(stack->contains(stack, &values[i]));
    }

    int value = 10;
    int* pvalue = &value;
    assert_false(stack->contains(stack, pvalue));

    *state = stack;
}


// Main ------------------------------------------------------------------------

int main()
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_stack_create),
            cmocka_unit_test(test_stack_is_empty),
            cmocka_unit_test(test_stack_push),
            cmocka_unit_test(test_stack_pop),
            cmocka_unit_test(test_stack_contains)
    };

    return cmocka_run_group_tests(tests, setup_stack, teardown_stack);
}