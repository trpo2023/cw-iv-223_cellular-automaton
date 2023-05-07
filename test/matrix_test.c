#include <stdlib.h>

#include <ctest.h>

#include <Cellular_automaton/cellular_automaton.h>

// basic test without setup/teardown
CTEST(suite1, test1)
{
    ASSERT_EQUAL(1, 1);
}

CTEST(suite1, free_test)
{
    Cellular_automaton* matrix = NULL;
    free_automaton(matrix);
}

CTEST_DATA(surround_test)
{
    Cellular_automaton* matrix;
};

// Optional setup function for suite, called before every test in suite
CTEST_SETUP(surround_test)
{
    CTEST_LOG(
            "%s() data=%p buffer=%p",
            __func__,
            (void*)data,
            (void*)data->matrix);
    data->matrix = create_simple_automaton(6, 6);
    data->matrix->matrix[0][0] = 1;
    data->matrix->matrix[0][1] = 1;
    data->matrix->matrix[0][2] = 1;
    data->matrix->matrix[0][3] = 1;
    data->matrix->matrix[0][5] = 1;
    data->matrix->matrix[1][0] = 1;
    data->matrix->matrix[1][1] = 1;
    data->matrix->matrix[1][2] = 1;
    data->matrix->matrix[1][4] = 1;
    data->matrix->matrix[2][0] = 1;
    data->matrix->matrix[2][1] = 1;
    data->matrix->matrix[2][2] = 1;
    data->matrix->matrix[2][3] = 1;
    data->matrix->matrix[2][5] = 1;
    data->matrix->matrix[3][4] = 1;
}

// Optional teardown function for suite, called after every test in suite
CTEST_TEARDOWN(surround_test)
{
    CTEST_LOG(
            "%s() data=%p buffer=%p",
            __func__,
            (void*)data,
            (void*)data->matrix);
    free_automaton(data->matrix);
}

// These tests are called with the struct* (named data) as argument
CTEST2(surround_test, Moore_test)
{
    ASSERT_EQUAL(8, Moore(1, 1, data->matrix));
    ASSERT_EQUAL(4, Moore(1, 4, data->matrix));
    ASSERT_EQUAL(4, Moore(2, 4, data->matrix));
    ASSERT_EQUAL(0, Moore(4, 1, data->matrix));
    ASSERT_EQUAL(1, Moore(4, 4, data->matrix));
}

CTEST2(surround_test, Von_Neumann_test)
{
    ASSERT_EQUAL(4, Von_Neumann(1, 1, data->matrix));
    ASSERT_EQUAL(0, Von_Neumann(1, 4, data->matrix));
    ASSERT_EQUAL(4, Von_Neumann(2, 4, data->matrix));
    ASSERT_EQUAL(0, Von_Neumann(4, 1, data->matrix));
    ASSERT_EQUAL(1, Von_Neumann(4, 4, data->matrix));
}

CTEST2(surround_test, Wolfish_test)
{
    ASSERT_EQUAL(4, Wolfish(1, 1, data->matrix));
    ASSERT_EQUAL(4, Wolfish(1, 4, data->matrix));
    ASSERT_EQUAL(0, Wolfish(2, 4, data->matrix));
    ASSERT_EQUAL(0, Wolfish(4, 1, data->matrix));
    ASSERT_EQUAL(0, Wolfish(4, 4, data->matrix));
}

CTEST2(surround_test, Moore_corner_test)
{
    ASSERT_EQUAL(3, Moore(0, 0, data->matrix));
    ASSERT_EQUAL(0, Moore(-1, 0, data->matrix));
}

CTEST2(surround_test, Von_Neumann_corner_test)
{
    ASSERT_EQUAL(2, Von_Neumann(0, 0, data->matrix));
    ASSERT_EQUAL(0, Von_Neumann(-1, 0, data->matrix));
}

CTEST2(surround_test, Wolfish_corner_test)
{
    ASSERT_EQUAL(1, Wolfish(0, 0, data->matrix));
    ASSERT_EQUAL(0, Wolfish(-1, 0, data->matrix));
}
