#include <Interaction/interaction.h>
#include <ctest.h>
#include <ncurses.h>
#include <stdlib.h>

CTEST(interaction, is_pause_check)
{
    _Bool is_pause = 0;
    _Bool is_edit = 0;
    char key = ' ';
    _Bool expected = 1;
    _Bool result = is_pause_check(is_pause, is_edit, key);
    ASSERT_EQUAL(expected, result);

    is_pause = 1;
    expected = 0;
    result = is_pause_check(is_pause, is_edit, key);
    ASSERT_EQUAL(expected, result);

    is_edit = 1;
    expected = 1;
    result = is_pause_check(is_pause, is_edit, key);
    ASSERT_EQUAL(expected, result);

    is_edit = 0;
    key = 'p';
    expected = 0;
    result = is_pause_check(is_pause, is_edit, key);
    ASSERT_EQUAL(expected, result);

    key = 'c';
    expected = 1;
    result = is_pause_check(is_pause, is_edit, key);
    ASSERT_EQUAL(expected, result);
}

CTEST(interaction, is_edit_mode_check)
{
    _Bool is_pause = 1;
    _Bool is_edit = 0;
    char key = 'e';
    _Bool expected = 1;
    _Bool result = is_edit_mode_check(is_pause, is_edit, key);
    ASSERT_EQUAL(expected, result);

    is_edit = 1;
    expected = 0;
    result = is_edit_mode_check(is_pause, is_edit, key);
    ASSERT_EQUAL(expected, result);

    is_pause = 0;
    expected = 1;
    result = is_edit_mode_check(is_pause, is_edit, key);
    ASSERT_EQUAL(expected, result);

    is_pause = 1;
    key = 'f';
    result = is_edit_mode_check(is_pause, is_edit, key);
    ASSERT_EQUAL(expected, result);
}

CTEST(interaction, cursor_movement)
{
    int key = 'c';
    coordinates cur;
    cur.x = 1;
    cur.y = 1;
    int win_h = 5;
    int win_l = 5;
    int expected_x = 1;
    int expected_y = 1;
    cur = cursor_movement(key, cur, win_h, win_l);
    ASSERT_EQUAL(expected_x, cur.x);
    ASSERT_EQUAL(expected_y, cur.y);

    key = KEY_DOWN;
    expected_x = 1;
    expected_y = 2;
    cur = cursor_movement(key, cur, win_h, win_l);
    ASSERT_EQUAL(expected_x, cur.x);
    ASSERT_EQUAL(expected_y, cur.y);

    expected_x = 1;
    expected_y = 2;
    cur = cursor_movement(key, cur, win_h, win_l);
    ASSERT_EQUAL(expected_x, cur.x);
    ASSERT_EQUAL(expected_y, cur.y);

    key = KEY_UP;
    expected_x = 1;
    expected_y = 1;
    cur = cursor_movement(key, cur, win_h, win_l);
    ASSERT_EQUAL(expected_x, cur.x);
    ASSERT_EQUAL(expected_y, cur.y);

    expected_x = 1;
    expected_y = 0;
    cur = cursor_movement(key, cur, win_h, win_l);
    cur = cursor_movement(key, cur, win_h, win_l);
    ASSERT_EQUAL(expected_x, cur.x);
    ASSERT_EQUAL(expected_y, cur.y);

    key = KEY_RIGHT;
    expected_x = 2;
    expected_y = 0;
    cur = cursor_movement(key, cur, win_h, win_l);
    ASSERT_EQUAL(expected_x, cur.x);
    ASSERT_EQUAL(expected_y, cur.y);

    expected_x = 2;
    expected_y = 0;
    cur = cursor_movement(key, cur, win_h, win_l);
    ASSERT_EQUAL(expected_x, cur.x);
    ASSERT_EQUAL(expected_y, cur.y);

    key = KEY_LEFT;
    expected_x = 1;
    expected_y = 0;
    cur = cursor_movement(key, cur, win_h, win_l);
    ASSERT_EQUAL(expected_x, cur.x);
    ASSERT_EQUAL(expected_y, cur.y);

    expected_x = 0;
    expected_y = 0;
    cur = cursor_movement(key, cur, win_h, win_l);
    cur = cursor_movement(key, cur, win_h, win_l);
    ASSERT_EQUAL(expected_x, cur.x);
    ASSERT_EQUAL(expected_y, cur.y);
}
CTEST(interaction, clear_field)
{
    int length = 20;
    int height = 60;
    _Bool expected = 0;
    _Bool result = 0;
    int** matrix = (int**)malloc(length * sizeof(int*));
    for (int i = 0; i < length; i++)
        matrix[i] = (int*)malloc(height * sizeof(int));

    int** result_matrix = (int**)malloc(length * sizeof(int*));
    for (int i = 0; i < length; i++)
        result_matrix[i] = (int*)malloc(height * sizeof(int));

    for (int i = 0; i < length; i++)
        for (int j = 0; j < height; j++) {
            matrix[i][j] = rand() % 2;
            result_matrix[i][j] = matrix[i][j];
        }
    char key = 'e';
    result_matrix = clear_field(key, matrix, length, height);
    for (int i = 0; i < length; i++)
        for (int j = 0; j < height; j++)
            if (result_matrix[i][j] != matrix[i][j]) {
                result = 1;
                break;
            }
    ASSERT_EQUAL(expected, result);

    key = 'c';
    result_matrix = clear_field(key, matrix, height, length);
    for (int i = 0; i < length; i++)
        for (int j = 0; j < height; j++)
            if (result_matrix[i][j]) {
                result = 1;
                break;
            }
    ASSERT_EQUAL(expected, result);
}
