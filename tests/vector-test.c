#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>
#include <stdlib.h>
#include "vector.h"

#define INT_EQ(x, y) assert_int_equal((x), *((int *) vector->data[(y)]))


// Fixture setup: creates a Vector.
static int setup_vector(void **state)
{
    Vector* vector = vector_create();
    assert_non_null(vector);
    *state = vector;
    return 0;
}

// Fixture teardown: frees a Vector.
static int teardown_vector(void **state)
{
    Vector* vector = (Vector*) *state;
    vector->free(vector);
    return 0;
}

char *str_value;

// Fixture setup: initializes a string.
static int setup_string()
{
    str_value = (char *)malloc(strlen("a string") + 1);
    if (!str_value)
        return -1;
    strcpy(str_value, "a string");
    return 0;
}

// Fixture teardown: frees a string.
static int teardown_string()
{
    if (!str_value)
        return -1;
    free(str_value);
    return 0;
}

int *values;

// Fixture setup: initializes array of integers.
static int setup_values()
{
    values = (int *)malloc(10 * sizeof(int));
    assert_non_null(values);
    for (int i = 0; i < 10; i++)
        values[i] = i;
    return 0;
}

// Fixture teardown: frees array of integers.
static int teardown_values()
{
    assert_non_null(values);
    free(values);
    return 0;
}

// Ensure that the given Vector has all the (integer) elements transmitted as arguments, in order.
void assert_vector(Vector* vector, int size, ...)
{
    va_list args;
    va_start(args, size);
    for (int i = 0; i < size; i++)
        INT_EQ(va_arg(args, int), i);
    va_end(args);
}

// Ensure that a new Vector is not NULL, has size 0 and default capacity.
static void test_vector_creation(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);
    assert_int_equal((int) vector->size, 0);
    assert_int_equal((int) vector->capacity, VECTOR_INIT_CAPACITY);
    *state = vector;
}

// Ensure that a Vector doubles its capacity when it has no more free slots when using vector_add().
static void test_vector_double_capacity_add(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    for (int i = 1; i <= 65; i++) {
        assert_int_equal(vector->add(vector, &i), 0);
        int capacity = (int) vector->capacity;

        if (i <= 4) assert_int_equal(capacity, 4);
        else if (i <= 8) assert_int_equal(capacity, 8);
        else if (i <= 16) assert_int_equal(capacity, 16);
        else if (i <= 32) assert_int_equal(capacity, 32);
        else if (i <= 64) assert_int_equal(capacity, 64);
        else assert_int_equal(capacity, 128);
    }

    *state = vector;
}

/*
 * Ensure that a Vector doubles its capacity when it has no more free slots when using
 * vector->insert().
 */
static void test_vector_double_capacity_insert(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    for (int i = 1; i <= 65; i++) {
        assert_int_equal(vector->insert(vector, &i, 0), 0);
        int capacity = (int) vector->capacity;

        if (i <= 4) assert_int_equal(capacity, 4);
        else if (i <= 8) assert_int_equal(capacity, 8);
        else if (i <= 16) assert_int_equal(capacity, 16);
        else if (i <= 32) assert_int_equal(capacity, 32);
        else if (i <= 64) assert_int_equal(capacity, 64);
        else assert_int_equal(capacity, 128);
    }

    *state = vector;
}

// Ensure that a Vector decreases its capacity by a factor of 2 when half of its slots become free.
static void test_vector_half_capacity(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    for (int i = 64; i >= 0; i--) {
        assert_non_null(vector->remove(vector, 0));
        int capacity = (int) vector->capacity;

        if (i > 32) assert_int_equal(capacity, 128);
        else if (i > 16) assert_int_equal(capacity, 64);
        else if (i > 8) assert_int_equal(capacity, 32);
        else if (i > 4) assert_int_equal(capacity, 16);
        else if (i > 2) assert_int_equal(capacity, 8);
        else assert_int_equal(capacity, 4);
    }

    *state = vector;
}

// Ensure that adding to a NULL Vector or Vector data results in failure.
static void test_vector_add_fail_null()
{
    int value = 5;

    Vector* vector = vector_create();
    assert_non_null(vector);
    assert_int_equal(vector->add(NULL, &value), -1);
    free(vector->data);
    vector->data = NULL;

    assert_int_equal(vector->add(vector, &value), -1);
    vector->free(vector);
}

// Ensure that a NULL item can be added to a Vector.
static void test_vector_add_null(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    int size = (int) vector->size;
    assert_int_equal(vector->add(vector, NULL), 0);
    assert_int_equal((int) vector->size, size + 1);
    assert_null(vector->data[vector->size - 1]);

    *state = vector;
}

// Ensure that an integer can be added to a Vector.
static void test_vector_add_int(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);
    int value = 5;
    int size = (int) vector->size;

    assert_int_equal(vector->add(vector, &value), 0);
    assert_int_equal((int) vector->size, size + 1);
    INT_EQ(value, vector->size - 1);

    *state = vector;
}

// Ensure that a double can be added to a Vector.
static void test_vector_add_double(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);
    double value = 567890.0123456789;
    int size = (int) vector->size;

    assert_int_equal(vector->add(vector, &value), 0);
    assert_int_equal((int) vector->size, size + 1);
    double *item = (double *) vector->data[vector->size- 1];
    assert_non_null(item);
    assert_true(value == *item);

    *state = vector;
}

// Ensure that a string can be added to a Vector.
static void test_vector_add_string(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);
    int size = (int) vector->size;

    assert_int_equal(vector->add(vector, str_value), 0);
    assert_int_equal((int) vector->size, size + 1);
    char *item = (char *) vector->data[vector->size - 1];
    assert_non_null(item);
    assert_string_equal(str_value, item);

    *state = vector;
}

// Ensure that a user-defined data structure can be added to a Vector.
static void test_vector_add_struct(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    typedef struct {
        int x;
        int y;
    } Point;

    Point value = {.x = 5, .y = 5};
    int size = (int) vector->size;

    assert_int_equal(vector->add(vector, &value), 0);
    assert_int_equal((int) vector->size, size + 1);

    Point *item = (Point *) vector->data[vector->size - 1];
    assert_non_null(item);
    assert_true(&value == item);
    assert_true(value.x == item->x && value.y == item->y);

    *state = vector;
}

// Ensure that insertion into NULL Vector or Vector data results in failure.
static void test_vector_insert_fail_null()
{
    int value = 7;

    Vector* vector = vector_create();
    assert_non_null(vector);
    assert_int_equal(vector->insert(NULL, &value, 0), -1);
    free(vector->data);
    vector->data = NULL;

    assert_int_equal(vector->insert(vector, &value, 0), -1);
    vector->free(vector);
}

// Ensure that insertion with invalid indexes results in failure.
static void test_vector_insert_fail_nonnull(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    int value = 7;
    assert_int_equal(vector->insert(vector, &value, -1), -1);
    assert_int_equal(vector->insert(vector, &value, 1), -1);

    *state = vector;
}

// Ensure that a NULL item can be inserted in a Vector at a specified index.
static void test_vector_insert_null(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);
    int size = (int) vector->size;

    assert_int_equal(vector->insert(vector, NULL, 0), 0);
    assert_int_equal((int) vector->size, size + 1);
    assert_null(vector->data[vector->size - 1]);

    *state = vector;
}

// Ensure that an integer can be inserted in a Vector at a specified index.
static void test_vector_insert_int(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);
    int value = 7;
    int size = (int) vector->size;

    assert_int_equal(vector->insert(vector, &value, 0), 0);
    assert_int_equal((int) vector->size, size + 1);
    INT_EQ(value, 0);

    *state = vector;
}

// Ensure that a double can be inserted in a Vector at a specified index.
static void test_vector_insert_double(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);
    double value = 567890.0123456789;
    int size = (int) vector->size;

    assert_int_equal(vector->insert(vector, &value, 0), 0);
    assert_int_equal((int) vector->size, size + 1);
    double *item = (double *) vector->data[0];
    assert_non_null(item);
    assert_true(value == *item);

    *state = vector;
}

// Ensure that a string can be inserted in a Vector at a specified index.
static void test_vector_insert_string(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);
    int size = (int) vector->size;

    assert_int_equal(vector->insert(vector, str_value, 0), 0);
    assert_int_equal((int) vector->size, size + 1);
    char *item = (char *) vector->data[0];
    assert_non_null(item);
    assert_string_equal(str_value, item);

    *state = vector;
}

// Ensure that a user-defined data structure can be inserted in a Vector at a specified index.
static void test_vector_insert_struct(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    typedef struct {
        int x;
        int y;
    } Point;

    Point value = {.x = 5, .y = 5};
    int size = (int) vector->size;

    assert_int_equal(vector->insert(vector, &value, 0), 0);
    assert_int_equal((int) vector->size, size + 1);

    Point *item = (Point *) vector->data[0];
    assert_non_null(item);
    assert_true(&value == item);
    assert_true(value.x == item->x && value.y == item->y);

    *state = vector;
}

// Setup fixture for inserting into a vector with 1 item.
static int setup_vector_ins_count_1(void **state)
{
    Vector* vector = vector_create();
    assert_non_null(vector);

    assert_int_equal(vector->add(vector, &values[9]), 0);
    *state = vector;

    return 0;
}

// Setup fixture for inserting into a vector with 2 items.
static int setup_vector_ins_count_2(void **state)
{
    setup_vector_ins_count_1(state);
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    assert_int_equal(vector->insert(vector, &values[8], 0), 0);
    *state = vector;

    return 0;
}

// Setup fixture for inserting into a vector with 3 items.
static int setup_vector_ins_count_3(void **state)
{
    setup_vector_ins_count_2(state);
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    assert_int_equal(vector->insert(vector, &values[7], 2), 0);
    *state = vector;

    return 0;
}

// Setup fixture for inserting into a vector with 4 items.
static int setup_vector_ins_count_4(void **state)
{
    setup_vector_ins_count_3(state);
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    assert_int_equal(vector->insert(vector, &values[6], 1), 0);
    *state = vector;

    return 0;
}

// Setup fixture for inserting into a vector with 5 items.
static int setup_vector_ins_count_5(void **state)
{
    setup_vector_ins_count_4(state);
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    assert_int_equal(vector->insert(vector, &values[0], 4), 0);
    *state = vector;

    return 0;
}

// Setup fixture for inserting into a vector with 6 items.
static int setup_vector_ins_count_6(void **state)
{
    setup_vector_ins_count_5(state);
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    assert_int_equal(vector->insert(vector, &values[3], 3), 0);
    *state = vector;

    return 0;
}

// Setup fixture for inserting into a vector with 7 items.
static int setup_vector_ins_count_7(void **state)
{
    setup_vector_ins_count_6(state);
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    assert_int_equal(vector->insert(vector, &values[1], 1), 0);
    *state = vector;

    return 0;
}

// Setup fixture for inserting into a vector with 8 items.
static int setup_vector_ins_count_8(void **state)
{
    setup_vector_ins_count_7(state);
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    assert_int_equal(vector->insert(vector, &values[5], 6), 0);
    *state = vector;

    return 0;
}

/*
 * Ensures that integer 9 can be inserted at index 0 when the Vector has no item.
 * Vector before insertion: [ ]
 * Vector after  insertion: [ 9 ]
 */
static void test_vector_insert_item_9_index_0(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    assert_int_equal(vector->insert(vector, &values[9], 0), 0);
    assert_int_equal((int) vector->size, 1);
    assert_int_equal((int) vector->capacity, VECTOR_INIT_CAPACITY);
    assert_vector(vector, 1, 9);

    *state = vector;
}

/*
 * Ensures that integer 8 can be inserted at index 0 when the Vector has 1 item.
 * Vector before insertion: [ 9 ]
 * Vector after  insertion: [ 8 9 ]
 */
static void test_vector_insert_item_8_index_0(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    assert_int_equal(vector->insert(vector, &values[8], 0), 0);
    assert_int_equal((int) vector->size, 2);
    assert_int_equal((int) vector->capacity, VECTOR_INIT_CAPACITY);
    assert_vector(vector, 2, 8, 9);

    *state = vector;
}

/*
 * Ensures that integer 7 can be inserted at index 2 when the Vector has 2 items.
 * Vector before insertion: [ 8 9 ]
 * Vector after  insertion: [ 8 9 7 ]
 */
static void test_vector_insert_item_7_index_2(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    assert_int_equal(vector->insert(vector, &values[7], 2), 0);
    assert_int_equal((int) vector->size, 3);
    assert_int_equal((int) vector->capacity, VECTOR_INIT_CAPACITY);
    assert_vector(vector, 3, 8, 9, 7);

    *state = vector;
}

/*
 * Ensures that integer 6 can be inserted at index 1 when the Vector has 3 items.
 * Vector before insertion: [ 8 9 7 ]
 * Vector after  insertion: [ 8 6 9 7 ]
 */
static void test_vector_insert_item_6_index_1(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    assert_int_equal(vector->insert(vector, &values[6], 1), 0);
    assert_int_equal((int) vector->size, 4);
    assert_int_equal((int) vector->capacity, VECTOR_INIT_CAPACITY);
    assert_vector(vector, 4, 8, 6, 9, 7);

    *state = vector;
}

/*
 * Ensures that integer 0 can be inserted at index 4 when the Vector has 4 items.
 * Vector before insertion: [ 8 6 9 7 ]
 * Vector after  insertion: [ 8 6 9 7 0 ]
*/
static void test_vector_insert_item_0_index_4(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    assert_int_equal(vector->insert(vector, &values[0], 4), 0);
    assert_int_equal((int) vector->size, 5);
    assert_int_equal((int) vector->capacity, 2*VECTOR_INIT_CAPACITY);
    assert_vector(vector, 5, 8, 6, 9, 7, 0);

    *state = vector;
}

/*
 * Ensures that integer 3 can be inserted at index 3 when the Vector has 5 items.
 * Vector before insertion: [ 8 6 9 7 0 ]
 * Vector after  insertion: [ 8 6 9 3 7 0 ]
*/
static void test_vector_insert_item_3_index_3(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    assert_int_equal(vector->insert(vector, &values[3], 3), 0);
    assert_int_equal((int) vector->size, 6);
    assert_int_equal((int) vector->capacity, 2*VECTOR_INIT_CAPACITY);
    assert_vector(vector, 6, 8, 6, 9, 3, 7, 0);

    *state = vector;
}

/*
 * Ensures that integer 1 can be inserted at index 1 when the Vector has 6 items.
 * Vector before insertion: [ 8 6 9 3 7 0 ]
 * Vector after  insertion: [ 8 1 6 9 3 7 0 ]
*/
static void test_vector_insert_item_1_index_1(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    assert_int_equal(vector->insert(vector, &values[1], 1), 0);
    assert_int_equal((int) vector->size, 7);
    assert_int_equal((int) vector->capacity, 2*VECTOR_INIT_CAPACITY);
    assert_vector(vector, 7, 8, 1, 6, 9, 3, 7, 0);

    *state = vector;
}

/*
 * Ensures that integer 5 can be inserted at index 6 when the Vector has 7 items.
 * Vector before insertion: [ 8 1 6 9 3 7 0 ]
 * Vector after  insertion: [ 8 1 6 9 3 7 5 0 ]
*/
static void test_vector_insert_item_5_index_6(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    assert_int_equal(vector->insert(vector, &values[5], 6), 0);
    assert_int_equal((int) vector->size, 8);
    assert_int_equal((int) vector->capacity, 2*VECTOR_INIT_CAPACITY);
    assert_vector(vector, 8, 8, 1, 6, 9, 3, 7, 5, 0);

    *state = vector;
}

/*
 * Ensures that integer 2 can be inserted at index 8 when the Vector has 8 items.
 * Vector before insertion: [ 8 1 6 9 3 7 5 0 ]
 * Vector after  insertion: [ 8 1 6 9 3 7 5 0 2 ]
*/
static void test_vector_insert_item_2_index_8(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    assert_int_equal(vector->insert(vector, &values[2], 8), 0);
    assert_int_equal((int) vector->size, 9);
    assert_int_equal((int) vector->capacity, 4*VECTOR_INIT_CAPACITY);
    assert_vector(vector, 9, 8, 1, 6, 9, 3, 7, 5, 0, 2);

    *state = vector;
}

// Setup fixture for deleting from a vector with 9 items.
static int setup_vector_delete(void **state)
{
    setup_vector_ins_count_8(state);
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    assert_int_equal(vector->insert(vector, &values[2], 8), 0);
    *state = vector;

    return 0;
}

// Ensures that deletion from a Vector with 9 items works as expected. 
static void test_vector_delete(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    int* item = vector->remove(vector, 8);
    assert_non_null(item);
    assert_int_equal(*item, 2);
    assert_int_equal((int) vector->size, 8);
    assert_int_equal((int) vector->capacity, 16);
    assert_vector(vector, 8, 8, 1, 6, 9, 3, 7, 5, 0);

    item = vector->remove(vector, 6);
    assert_non_null(item);
    assert_int_equal(*item, 5);
    assert_int_equal((int) vector->size, 7);
    assert_int_equal((int) vector->capacity, 16);
    assert_vector(vector, 7, 8, 1, 6, 9, 3, 7, 0);

    item = vector->remove(vector, 1);
    assert_non_null(item);
    assert_int_equal(*item, 1);
    assert_int_equal((int) vector->size, 6);
    assert_int_equal((int) vector->capacity, 16);
    assert_vector(vector, 6, 8, 6, 9, 3, 7, 0);

    item = vector->remove(vector, 3);
    assert_non_null(item);
    assert_int_equal(*item, 3);
    assert_int_equal((int) vector->size, 5);
    assert_int_equal((int) vector->capacity, 16);
    assert_vector(vector, 5, 8, 6, 9, 7, 0);

    item = vector->remove(vector, 4);
    assert_non_null(item);
    assert_int_equal(*item, 0);
    assert_int_equal((int) vector->size, 4);
    assert_int_equal((int) vector->capacity, 8);
    assert_vector(vector, 4, 8, 6, 9, 7);

    item = vector->remove(vector, 1);
    assert_non_null(item);
    assert_int_equal(*item, 6);
    assert_int_equal((int) vector->size, 3);
    assert_int_equal((int) vector->capacity, 8);
    assert_vector(vector, 3, 8, 9, 7);

    item = vector->remove(vector, 2);
    assert_non_null(item);
    assert_int_equal(*item, 7);
    assert_int_equal((int) vector->size, 2);
    assert_int_equal((int) vector->capacity, 4);
    assert_vector(vector, 2, 8, 9);

    item = vector->remove(vector, 0);
    assert_non_null(item);
    assert_int_equal(*item, 8);
    assert_int_equal((int) vector->size, 1);
    assert_int_equal((int) vector->capacity, 4);
    assert_vector(vector, 1, 9);

    item = vector->remove(vector, 0);
    assert_non_null(item);
    assert_int_equal(*item, 9);
    assert_int_equal((int) vector->size, 0);
    assert_int_equal((int) vector->capacity, 4);

    *state = vector;
}

// Ensures that the 'contains' operation works as expected.
static void test_vector_contains(void **state)
{
    Vector* vector = (Vector*) *state;
    assert_non_null(vector);

    assert_false(vector->contains(NULL, &values[3]));
    for (int i = 0; i < 10; i++) {
        vector->add(vector, &values[i]);
        assert_true(vector->contains(vector, &values[i]));
    }
    int value = 10;
    int* pvalue = &value;
    assert_false(vector->contains(vector, pvalue));

    *state = vector;
}

int run_tests_capacity()
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_vector_creation),
            cmocka_unit_test(test_vector_double_capacity_add),
            cmocka_unit_test(test_vector_half_capacity),
            cmocka_unit_test(test_vector_double_capacity_insert),
            cmocka_unit_test(test_vector_half_capacity)
    };

    return cmocka_run_group_tests(tests, setup_vector, teardown_vector);
}

int run_tests_addition()
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_vector_add_fail_null),
            cmocka_unit_test(test_vector_add_null),
            cmocka_unit_test(test_vector_add_int),
            cmocka_unit_test(test_vector_add_double),
            cmocka_unit_test_setup_teardown(
                    test_vector_add_string, setup_string, teardown_string),
            cmocka_unit_test(test_vector_add_struct)
    };
    return cmocka_run_group_tests(tests, setup_vector, teardown_vector);
}

int run_tests_insertion()
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_vector_insert_fail_null),
            cmocka_unit_test(test_vector_insert_fail_nonnull),
            cmocka_unit_test(test_vector_insert_null),
            cmocka_unit_test(test_vector_insert_int),
            cmocka_unit_test(test_vector_insert_double),
            cmocka_unit_test_setup_teardown(
                    test_vector_insert_string, setup_string, teardown_string),
            cmocka_unit_test(test_vector_insert_struct)

    };
    return cmocka_run_group_tests(tests, setup_vector, teardown_vector);
}

int run_tests_sequence()
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test_setup_teardown(
                    test_vector_insert_item_9_index_0,
                    setup_vector,
                    teardown_vector),
            cmocka_unit_test_setup_teardown(
                    test_vector_insert_item_8_index_0,
                    setup_vector_ins_count_1,
                    teardown_vector),
            cmocka_unit_test_setup_teardown(
                    test_vector_insert_item_7_index_2,
                    setup_vector_ins_count_2,
                    teardown_vector),
            cmocka_unit_test_setup_teardown(
                    test_vector_insert_item_6_index_1,
                    setup_vector_ins_count_3,
                    teardown_vector),
            cmocka_unit_test_setup_teardown(
                    test_vector_insert_item_0_index_4,
                    setup_vector_ins_count_4,
                    teardown_vector),
            cmocka_unit_test_setup_teardown(
                    test_vector_insert_item_3_index_3,
                    setup_vector_ins_count_5,
                    teardown_vector),
            cmocka_unit_test_setup_teardown(
                    test_vector_insert_item_1_index_1,
                    setup_vector_ins_count_6,
                    teardown_vector),
            cmocka_unit_test_setup_teardown(
                    test_vector_insert_item_5_index_6,
                    setup_vector_ins_count_7,
                    teardown_vector),
            cmocka_unit_test_setup_teardown(
                    test_vector_insert_item_2_index_8,
                    setup_vector_ins_count_8,
                    teardown_vector)
    };
    return cmocka_run_group_tests(tests, setup_values, teardown_values);
}

int run_tests_deletion()
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test_setup_teardown(
                    test_vector_delete,
                    setup_vector_delete,
                    teardown_vector)
    };

    return cmocka_run_group_tests(tests, setup_values, teardown_values);
}

int run_tests_contains()
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test_setup_teardown(
                    test_vector_contains,
                    setup_vector,
                    teardown_vector)
    };

    return cmocka_run_group_tests(tests, setup_values, teardown_values);
}

int main()
{
    int r_cap = run_tests_capacity();
    int r_add = run_tests_addition();
    int r_ins = run_tests_insertion();
    int r_del = run_tests_deletion();
    int r_seq = run_tests_sequence();
    int r_has = run_tests_contains();

    return r_cap && r_add && r_ins && r_del && r_seq && r_has;
}
