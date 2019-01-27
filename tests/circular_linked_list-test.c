#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>
#include <stdlib.h>
#include "circular_linked_list.h"

// Fixtures --------------------------------------------------------------------

int values[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

// Fixture setup: creates a CircularLinkedList.
static int setup_circular_linked_list(void** state)
{
    CircularLinkedList* list = circular_linked_list_create();
    assert_non_null(list);
    *state = list;
    return 0;
}

// Fixture setup: creates a CircularLinkedList with one element.
static int setup_circular_linked_list_one_element(void** state)
{
    CircularLinkedList* list = circular_linked_list_create();
    assert_non_null(list);
    assert_int_equal(list->insert_start(list, &values[0]), 0);
    *state = list;
    return 0;
}

// Fixture setup: creates a CircularLinkedList with two elements.
static int setup_circular_linked_list_two_elements(void** state)
{
    CircularLinkedList* list = circular_linked_list_create();
    assert_non_null(list);
    assert_int_equal(list->insert_start(list, &values[0]), 0);
    assert_int_equal(list->insert_start(list, &values[1]), 0);
    *state = list;
    return 0;
}

/*
 * Fixture setup: creates a CircularLinkedList and inserts some values in it, at the start of the
 * list.
 */
static int setup_circular_linked_list_insert_start(void** state)
{
    CircularLinkedList* list = circular_linked_list_create();
    assert_non_null(list);
    for (int i = 9; i >= 0; i--)
        assert_int_equal(list->insert_start(list, &values[i]), 0);
    *state = list;
    return 0;
}

/*
 * Fixture setup: creates a CircularLinkedList and inserts some values in it, at the end of the
 * list.
 */
static int setup_circular_linked_list_insert_end(void** state)
{
    CircularLinkedList* list = circular_linked_list_create();
    assert_non_null(list);
    for (int i = 0; i < 10; i++)
        assert_int_equal(list->insert_end(list, &values[i]), 0);
    *state = list;
    return 0;
}

/*
 * Fixture setup: creates a CircularLinkedList and inserts some values in it, at specific indexes of
 * the list.
 */
static int setup_circular_linked_list_insert_at(void** state)
{
    CircularLinkedList* list = circular_linked_list_create();
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

// Fixture teardown: frees a CircularLinkedList.
static int teardown_circular_linked_list(void** state)
{
    CircularLinkedList* list = (CircularLinkedList*) *state;
    list->free(list);
    return 0;
}


// Tests -----------------------------------------------------------------------

// Tests list creation
static void test_circular_linked_list_create(void** state)
{
    CircularLinkedList* list = (CircularLinkedList*) *state;
    assert_non_null(list);
    *state = list;
}

// Tests list deallocation
static void test_deallocation(void** state)
{
    CircularLinkedList* list = (CircularLinkedList*) *state;
    list->free(list);
}

// Tests whether the list is empty upon creation
static void test_circular_linked_list_is_empty(void** state)
{
    CircularLinkedList* list = (CircularLinkedList*) *state;
    assert_true(list->is_empty(list));
    assert_int_equal(list->size, 0);
    *state = list;
}

// Tests insertion at the beginning of the list
static void test_circular_linked_list_insert_start(void** state)
{
    CircularLinkedList* list = (CircularLinkedList*) *state;
    list->insert_start(list, &values[0]);
    assert_false(list->is_empty(list));
    assert_int_equal(list->size, 1);
    *state = list;
}

// Tests insertion at the end of the list
static void test_circular_linked_list_insert_end(void** state)
{
    CircularLinkedList* list = (CircularLinkedList*) *state;
    list->insert_end(list, &values[0]);
    assert_false(list->is_empty(list));
    assert_int_equal(list->size, 1);
    *state = list;
}

// Tests insertion at a given index of the list
static void test_circular_linked_list_insert_at(void** state)
{
    CircularLinkedList* list = (CircularLinkedList*) *state;
    list->insert_at(list, &values[0], 0);
    assert_false(list->is_empty(list));
    assert_int_equal(list->size, 1);
    *state = list;
}

// Tests deletion at the beginning of the list
static void test_circular_linked_list_delete_start(void** state)
{
    CircularLinkedList* list = (CircularLinkedList*) *state;
    for (int i = 0; i < 10; i++) {
        int value = *((int*) list->remove_start(list));
        assert_int_equal(value, i);
        i == 9 ? assert_true(list->is_empty(list)) : assert_false(list->is_empty(list));
        assert_int_equal(list->size, 9 - i);
    }
    *state = list;
}

// Tests deletion at the end of the list
static void test_circular_linked_list_delete_end(void** state)
{
    CircularLinkedList* list = (CircularLinkedList*) *state;
    for (int i = 0; i < 10; i++) {
        int value = *((int*) list->remove_end(list));
        assert_int_equal(value, 9 - i);
        i == 9 ? assert_true(list->is_empty(list)) : assert_false(list->is_empty(list));
        assert_int_equal(list->size, 9 - i);
    }
    *state = list;
}

// Tests deletion at a given index of the list
static void test_circular_linked_list_delete_at(void** state)
{
    CircularLinkedList* list = (CircularLinkedList*) *state;

    int* value = list->remove_at(list, -1);
    assert_null(value);
    value = list->remove_at(list, 10);
    assert_null(value);

    int i;
    for (i = 5; i < 10; i++) {
        int value = *((int*) list->remove_at(list, 5));
        assert_int_equal(value, i);
        assert_false(list->is_empty(list));
        assert_int_equal(list->size, 10 - i + 4);
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

// Ensures that the 'contains' operation works as expected.
static void test_circular_linked_list_contains(void** state)
{
    CircularLinkedList* list = (CircularLinkedList*) *state;
    assert_non_null(list);

    assert_false(list->contains(NULL, &values[3]));
    for (int i = 0; i < 10; i++)
        assert_true(list->contains(list, &values[i]));
    int value = 10;
    int* pvalue = &value;
    assert_false(list->contains(list, pvalue));

    *state = list;
}

// Main ------------------------------------------------------------------------

int main()
{
    const struct CMUnitTest tests_creation[] = {
            cmocka_unit_test(test_circular_linked_list_create),
            cmocka_unit_test(test_circular_linked_list_is_empty)
    };

    const struct CMUnitTest tests_deallocation[] = {
            cmocka_unit_test(test_deallocation)
    };

    const struct CMUnitTest tests_insertion[] = {
            cmocka_unit_test_setup_teardown(
                    test_circular_linked_list_insert_start,
                    setup_circular_linked_list,
                    teardown_circular_linked_list),
            cmocka_unit_test_setup_teardown(
                    test_circular_linked_list_insert_end,
                    setup_circular_linked_list,
                    teardown_circular_linked_list),
            cmocka_unit_test_setup_teardown(
                    test_circular_linked_list_insert_at,
                    setup_circular_linked_list,
                    teardown_circular_linked_list),
    };

    const struct CMUnitTest tests_deletion[] = {
            cmocka_unit_test_setup_teardown(
                    test_circular_linked_list_delete_start,
                    setup_circular_linked_list_insert_start,
                    teardown_circular_linked_list),
            cmocka_unit_test_setup_teardown(
                    test_circular_linked_list_delete_start,
                    setup_circular_linked_list_insert_end,
                    teardown_circular_linked_list),
            cmocka_unit_test_setup_teardown(
                    test_circular_linked_list_delete_start,
                    setup_circular_linked_list_insert_at,
                    teardown_circular_linked_list),
            cmocka_unit_test_setup_teardown(
                    test_circular_linked_list_delete_end,
                    setup_circular_linked_list_insert_start,
                    teardown_circular_linked_list),
            cmocka_unit_test_setup_teardown(
                    test_circular_linked_list_delete_end,
                    setup_circular_linked_list_insert_end,
                    teardown_circular_linked_list),
            cmocka_unit_test_setup_teardown(
                    test_circular_linked_list_delete_end,
                    setup_circular_linked_list_insert_at,
                    teardown_circular_linked_list),
            cmocka_unit_test_setup_teardown(
                    test_circular_linked_list_delete_at,
                    setup_circular_linked_list_insert_start,
                    teardown_circular_linked_list),
            cmocka_unit_test_setup_teardown(
                    test_circular_linked_list_delete_at,
                    setup_circular_linked_list_insert_end,
                    teardown_circular_linked_list),
            cmocka_unit_test_setup_teardown(
                    test_circular_linked_list_delete_at,
                    setup_circular_linked_list_insert_at,
                    teardown_circular_linked_list),

    };

    const struct CMUnitTest tests_contains[] = {
            cmocka_unit_test_setup_teardown(
                    test_circular_linked_list_contains,
                    setup_circular_linked_list_insert_start,
                    teardown_circular_linked_list)
    };

    int status_creation = cmocka_run_group_tests(
            tests_creation, setup_circular_linked_list, teardown_circular_linked_list);
    int status_deallocation1 = cmocka_run_group_tests(
            tests_deallocation, setup_circular_linked_list_one_element, NULL);
    int status_deallocation2 = cmocka_run_group_tests(
            tests_deallocation, setup_circular_linked_list_two_elements, NULL);
    int status_insertion = cmocka_run_group_tests(tests_insertion, NULL, NULL);
    int status_deletion = cmocka_run_group_tests(tests_deletion, NULL, NULL);
    int status_contains = cmocka_run_group_tests(tests_contains, NULL, NULL);

    return status_creation && status_deallocation1 && status_deallocation2
           && status_insertion && status_deletion && status_contains;
}
