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

int values[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

// Fixture setup: creates a LinkedList.
static int setup_linked_list(void** state)
{
    LinkedList* list = linked_list_create();
    assert_non_null(list);
    *state = list;
    return 0;
}

// Fixture setup: creates a LinkedList and inserts some values in it, at the start of the list.
static int setup_linked_list_insert_start(void **state)
{
    LinkedList* list = linked_list_create();
    assert_non_null(list);
    for (int i = 9; i >= 0; i--)
        assert_int_equal(list->insert_start(list, &values[i]), 0);
    *state = list;
    return 0;
}

// Fixture setup: creates a LinkedList and inserts some values in it, at the end of the list.
static int setup_linked_list_insert_end(void **state)
{
    LinkedList* list = linked_list_create();
    assert_non_null(list);
    for (int i = 0; i < 10; i++)
        assert_int_equal(list->insert_end(list, &values[i]), 0);
    *state = list;
    return 0;
}

/*
 * Fixture setup: creates a LinkedList and inserts some values in it, at specific indexes of the
 * list.
 */
static int setup_linked_list_insert_at(void **state)
{
    LinkedList* list = linked_list_create();
    assert_non_null(list);
    assert_int_equal(list->insert_at(list, &values[0], 0), 0);   // 0
    assert_int_equal(list->insert_at(list, &values[1], 1), 0);   // 0 1
    assert_int_equal(list->insert_at(list, &values[9], -1), -1); // 0 1
    assert_int_equal(list->insert_at(list, &values[9], 9), -1);  // 0 1
    assert_int_equal(list->insert_at(list, &values[9], 3), -1);  // 0 1
    assert_int_equal(list->insert_at(list, &values[9], 2), 0);   // 0 1 9
    assert_int_equal(list->insert_at(list, &values[8], 2), 0);   // 0 1 8 9
    assert_int_equal(list->insert_at(list, &values[5], 2), 0);   // 0 1 5 8 9
    assert_int_equal(list->insert_at(list, &values[2], 2), 0);   // 0 1 2 5 8 9
    assert_int_equal(list->insert_at(list, &values[4], 3), 0);   // 0 1 2 4 5 8 9
    assert_int_equal(list->insert_at(list, &values[3], 3), 0);   // 0 1 2 3 4 5 8 9
    assert_int_equal(list->insert_at(list, &values[6], 6), 0);   // 0 1 2 3 4 5 6 8 9
    assert_int_equal(list->insert_at(list, &values[7], 7), 0);   // 0 1 2 3 4 5 6 7 8 9
    *state = list;
    return 0;
}

// Fixture teardown: frees a LinkedList.
static int teardown_linked_list(void** state)
{
    LinkedList* list = (LinkedList*) *state;
    list->free(list);
    return 0;
}


// Tests -----------------------------------------------------------------------

// Tests list creation
static void test_linked_list_create(void** state)
{
    LinkedList* list = (LinkedList*) *state;
    assert_non_null(list);
    *state = list;
}

// Tests whether the list is empty upon creation
static void test_linked_list_is_empty(void** state)
{
    LinkedList* list = (LinkedList*) *state;
    assert_true(list->is_empty(list));
    assert_int_equal(list->size, 0);
    *state = list;
}

// Tests insertion at the beginning of the list
static void test_linked_list_insert_start(void** state)
{
    LinkedList* list = (LinkedList*) *state;
    list->insert_start(list, &values[0]);
    assert_false(list->is_empty(list));
    assert_int_equal(list->size, 1);
    *state = list;
}

// Tests insertion at the end of the list
static void test_linked_list_insert_end(void** state)
{
    LinkedList* list = (LinkedList*) *state;
    list->insert_end(list, &values[0]);
    assert_false(list->is_empty(list));
    assert_int_equal(list->size, 1);
    *state = list;
}

// Tests insertion at a given index of the list
static void test_linked_list_insert_at(void** state)
{
    LinkedList* list = (LinkedList*) *state;
    list->insert_at(list, &values[0], 0);
    assert_false(list->is_empty(list));
    assert_int_equal(list->size, 1);
    *state = list;
}

// Tests deletion at the beginning of the list
static void test_linked_list_delete_start(void** state)
{
    LinkedList* list = (LinkedList*) *state;
    for (int i = 0; i < 10; i++) {
        int value = *((int*) list->remove_start(list));
        assert_int_equal(value, i);
        i == 9 ? assert_true(list->is_empty(list)) : assert_false(list->is_empty(list));
        assert_int_equal(list->size, 9 - i);
    }
    *state = list;
}

// Tests deletion at the end of the list
static void test_linked_list_delete_end(void** state)
{
    LinkedList* list = (LinkedList*) *state;
    for (int i = 0; i < 10; i++) {
        int value = *((int*) list->remove_end(list));
        assert_int_equal(value, 9 - i);
        i == 9 ? assert_true(list->is_empty(list)) : assert_false(list->is_empty(list));
        assert_int_equal(list->size, 9 - i);
    }
    *state = list;
}

// Tests deletion at a given index of the list
static void test_linked_list_delete_at(void** state)
{
    LinkedList* list = (LinkedList*) *state;

    int* value = list->remove_at(list, -1);
    assert_null(value);
    value = list->remove_at(list, 10);
    assert_null(value);

    int i;
    for (i = 5; i < 10; i++) {
        int value = *((int*) list->remove_at(list, 5));
        assert_int_equal(value, i);
        assert_false(list->is_empty(list));
        assert_int_equal(list->size, 10 - i + 4); // 59 68 76 86 95
    }

    value = list->remove_at(list, 2);
    assert_int_equal(*value, 2);
    assert_int_equal(list->size, 4);

    value = list->remove_at(list, 2);
    assert_int_equal(*value, 3);
    assert_int_equal(list->size, 3);

    value = list->remove_at(list, 2);
    assert_int_equal(*value, 4);
    assert_int_equal(list->size, 2);

    value = list->remove_at(list, 2);
    assert_null(value);

    value = list->remove_at(list, 1);
    assert_int_equal(*value, 1);
    assert_int_equal(list->size, 1);

    value = list->remove_at(list, 0);
    assert_int_equal(*value, 0);
    assert_int_equal(list->size, 0);

    assert_true(list->is_empty(list));

    value = list->remove_at(list, 0);
    assert_null(value);

    value = list->remove_at(list, 1);
    assert_null(value);

    assert_true(list->is_empty(list));

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
            cmocka_unit_test_setup_teardown(
                    test_linked_list_insert_at, setup_linked_list, teardown_linked_list),
    };

    const struct CMUnitTest tests_deletion[] = {
            cmocka_unit_test_setup_teardown(
                    test_linked_list_delete_start,
                    setup_linked_list_insert_start,
                    teardown_linked_list),
            cmocka_unit_test_setup_teardown(
                    test_linked_list_delete_start,
                    setup_linked_list_insert_end,
                    teardown_linked_list),
            cmocka_unit_test_setup_teardown(
                    test_linked_list_delete_start,
                    setup_linked_list_insert_at,
                    teardown_linked_list),
            cmocka_unit_test_setup_teardown(
                    test_linked_list_delete_end,
                    setup_linked_list_insert_start,
                    teardown_linked_list),
            cmocka_unit_test_setup_teardown(
                    test_linked_list_delete_end,
                    setup_linked_list_insert_end,
                    teardown_linked_list),
            cmocka_unit_test_setup_teardown(
                    test_linked_list_delete_end,
                    setup_linked_list_insert_at,
                    teardown_linked_list),
            cmocka_unit_test_setup_teardown(
                    test_linked_list_delete_at,
                    setup_linked_list_insert_start,
                    teardown_linked_list),
            cmocka_unit_test_setup_teardown(
                    test_linked_list_delete_at,
                    setup_linked_list_insert_end,
                    teardown_linked_list),
            cmocka_unit_test_setup_teardown(
                    test_linked_list_delete_at,
                    setup_linked_list_insert_at,
                    teardown_linked_list),

    };

    int status_creation = cmocka_run_group_tests(
            tests_creation, setup_linked_list, teardown_linked_list);
    int status_insertion = cmocka_run_group_tests(tests_insertion, NULL, NULL);
    int status_deletion = cmocka_run_group_tests(tests_deletion, NULL, NULL);

    return status_creation && status_insertion && status_deletion;
}
