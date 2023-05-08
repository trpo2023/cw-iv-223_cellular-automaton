#include <Input/input_user_interface.h>
#include <ctest.h>

CTEST(input_user_interface, check_num_of_arguments)
{
    int argc = 8;
    _Bool expected = 0;
    _Bool result = check_num_of_arguments(argc);
    ASSERT_EQUAL(expected, result);

    argc = 7;
    expected = 1;
    result = check_num_of_arguments(argc);
    ASSERT_EQUAL(expected, result);
}

CTEST(input_user_interface, get_environmnt)
{
    char* argv[8];
    argv[1] = "-von_neumann\0";
    int expected = 1;
    int result = get_environmnt(argv);
    ASSERT_EQUAL(expected, result);

    argv[1] = "-wolfish\0";
    expected = 2;
    result = get_environmnt(argv);
    ASSERT_EQUAL(expected, result);

    argv[1] = "-moore\0";
    expected = 3;
    result = get_environmnt(argv);
    ASSERT_EQUAL(expected, result);

    argv[1] = "-more\0";
    expected = 0;
    result = get_environmnt(argv);
    ASSERT_EQUAL(expected, result);
}

CTEST(input_user_interface, cell_rules_check)
{
    char* argv[8];
    // окрестность фон неймана
    int env = 1;
    for (; env <= 2; env++) {
        argv[MIN_TO_NEW_IND] = "0\0";
        argv[MAX_TO_NEW_IND] = "1\0";
        argv[MIN_TO_DIE_IND] = "3\0";
        argv[MAX_TO_DIE_IND] = "4\0";

        int expected = 0;
        int result = cell_rules_check(MIN_TO_NEW_IND, env, argv);
        ASSERT_EQUAL(expected, result);

        expected = 1;
        result = cell_rules_check(MAX_TO_NEW_IND, env, argv);
        ASSERT_EQUAL(expected, result);

        expected = 3;
        result = cell_rules_check(MIN_TO_DIE_IND, env, argv);
        ASSERT_EQUAL(expected, result);

        expected = 4;
        result = cell_rules_check(MAX_TO_DIE_IND, env, argv);
        ASSERT_EQUAL(expected, result);

        argv[MIN_TO_NEW_IND] = "e\0";
        expected = -1;
        result = cell_rules_check(MIN_TO_NEW_IND, env, argv);
        ASSERT_EQUAL(expected, result);

        argv[MIN_TO_NEW_IND] = "5\0";
        argv[MAX_TO_NEW_IND] = "5\0";
        argv[MIN_TO_DIE_IND] = "5\0";
        argv[MAX_TO_DIE_IND] = "5\0";

        result = cell_rules_check(MIN_TO_NEW_IND, env, argv);
        ASSERT_EQUAL(expected, result);

        result = cell_rules_check(MAX_TO_NEW_IND, env, argv);
        ASSERT_EQUAL(expected, result);

        result = cell_rules_check(MIN_TO_DIE_IND, env, argv);
        ASSERT_EQUAL(expected, result);

        result = cell_rules_check(MAX_TO_DIE_IND, env, argv);
        ASSERT_EQUAL(expected, result);

        argv[MIN_TO_NEW_IND] = "-1\0";
        argv[MAX_TO_NEW_IND] = "-1\0";
        argv[MIN_TO_DIE_IND] = "-1\0";
        argv[MAX_TO_DIE_IND] = "-1\0";

        result = cell_rules_check(MIN_TO_NEW_IND, env, argv);
        ASSERT_EQUAL(expected, result);

        result = cell_rules_check(MAX_TO_NEW_IND, env, argv);
        ASSERT_EQUAL(expected, result);

        result = cell_rules_check(MIN_TO_DIE_IND, env, argv);
        ASSERT_EQUAL(expected, result);

        result = cell_rules_check(MAX_TO_DIE_IND, env, argv);
        ASSERT_EQUAL(expected, result);
    }
    // окрестность Мура
    argv[MIN_TO_NEW_IND] = "5\0";
    argv[MAX_TO_NEW_IND] = "3\0";
    argv[MIN_TO_DIE_IND] = "7\0";
    argv[MAX_TO_DIE_IND] = "8\0";

    int expected = 5;
    int result = cell_rules_check(MIN_TO_NEW_IND, env, argv);
    ASSERT_EQUAL(expected, result);

    expected = 3;
    result = cell_rules_check(MAX_TO_NEW_IND, env, argv);
    ASSERT_EQUAL(expected, result);

    expected = 7;
    result = cell_rules_check(MIN_TO_DIE_IND, env, argv);
    ASSERT_EQUAL(expected, result);

    expected = 8;
    result = cell_rules_check(MAX_TO_DIE_IND, env, argv);
    ASSERT_EQUAL(expected, result);

    argv[MIN_TO_NEW_IND] = "9\0";
    argv[MAX_TO_NEW_IND] = "9\0";
    argv[MIN_TO_DIE_IND] = "9\0";
    argv[MAX_TO_DIE_IND] = "9\0";

    expected = -1;
    result = cell_rules_check(MIN_TO_NEW_IND, env, argv);
    ASSERT_EQUAL(expected, result);

    result = cell_rules_check(MAX_TO_NEW_IND, env, argv);
    ASSERT_EQUAL(expected, result);

    result = cell_rules_check(MIN_TO_DIE_IND, env, argv);
    ASSERT_EQUAL(expected, result);

    result = cell_rules_check(MAX_TO_DIE_IND, env, argv);
    ASSERT_EQUAL(expected, result);
}

CTEST(input_user_interface, get_error_code)
{
    int env = 1, ctnn = 4, ctnx = 2, ctdn = 3, ctdx = 1, l = 1, h = 1;
    int expected = 0;
    int result = get_error_code(env, ctnn, ctnx, ctdn, ctdx, l, h);
    ASSERT_EQUAL(expected, result);

    expected = 7;
    h = 0;
    result = get_error_code(env, ctnn, ctnx, ctdn, ctdx, l, h);
    ASSERT_EQUAL(expected, result);

    expected = 6;
    l = 0;
    result = get_error_code(env, ctnn, ctnx, ctdn, ctdx, l, h);
    ASSERT_EQUAL(expected, result);

    expected = 5;
    ctdx = -1;
    result = get_error_code(env, ctnn, ctnx, ctdn, ctdx, l, h);
    ASSERT_EQUAL(expected, result);

    expected = 4;
    ctdn = -1;
    result = get_error_code(env, ctnn, ctnx, ctdn, ctdx, l, h);
    ASSERT_EQUAL(expected, result);

    expected = 3;
    ctnx = -1;
    result = get_error_code(env, ctnn, ctnx, ctdn, ctdx, l, h);
    ASSERT_EQUAL(expected, result);

    expected = 2;
    ctnn = -1;
    result = get_error_code(env, ctnn, ctnx, ctdn, ctdx, l, h);
    ASSERT_EQUAL(expected, result);

    expected = 1;
    env = 0;
    result = get_error_code(env, ctnn, ctnx, ctdn, ctdx, l, h);
    ASSERT_EQUAL(expected, result);
}
