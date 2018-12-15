//
// Created by Alexandra Zaharia on 14/12/18.
//

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>
#include <stdlib.h>
#include "linked_list.h"

// Fixtures --------------------------------------------------------------------

/* Fixture setup: creates a LinkedList. */
static int setup_linked_list(void** state)
{
    LinkedList* list = linked_list_create();
    assert_non_null(list);
    *state = list;
    return 0;
}

/* Fixture teardown: frees a LinkedList. */
static int teardown_linked_list(void** state)
{
    LinkedList* list = (LinkedList*) *state;
    list->free(list);
    return 0;
}

int values[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

// Tests -----------------------------------------------------------------------

static void test_linked_list_create(void** state)
{
    LinkedList* list = (LinkedList*) *state;
    assert_non_null(list);
    *state = list;
}

static void test_linked_list_is_empty(void** state)
{
    LinkedList* list = (LinkedList*) *state;
    assert_true(list->is_empty(list));
    assert_int_equal(list->size, 0);
    *state = list;
}

static void test_linked_list_insert_start(void** state)
{
    LinkedList* list = (LinkedList*) *state;
    list->insert_start(list, &values[0]);
    assert_false(list->is_empty(list));
    assert_int_equal(list->size, 1);
    *state = list;
}

static void test_linked_list_insert_end(void** state)
{
    LinkedList* list = (LinkedList*) *state;
    list->insert_end(list, &values[0]);
    assert_false(list->is_empty(list));
    assert_int_equal(list->size, 1);
    *state = list;
}

// Main ------------------------------------------------------------------------

int main()
{
    const struct CMUnitTest tests_creation[] = {
            cmocka_unit_test(test_linked_list_create),
            cmocka_unit_test(test_linked_list_is_empty)
    };

    const struct CMUnitTest tests_insertion[] = {
            cmocka_unit_test_setup_teardown(
                    test_linked_list_insert_start, setup_linked_list, teardown_linked_list),
            cmocka_unit_test_setup_teardown(
                    test_linked_list_insert_end, setup_linked_list, teardown_linked_list),
    };

    int status_creation = cmocka_run_group_tests(
            tests_creation, setup_linked_list, teardown_linked_list);
    int status_insertion = cmocka_run_group_tests(tests_insertion, NULL, NULL);

    return status_creation && status_insertion;
}