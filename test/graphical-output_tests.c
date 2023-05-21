#include <Cellular_automaton/cellular_automaton.h>
#include <Screen/graphical-output.h>
#include <ctest.h>
#include <ncurses.h>

CTEST(graphical_output, win_size_check)
{
    int term_h = 100, term_l = 100;
    int h = 40, l = 20;
    _Bool expected = 0;
    _Bool result = win_size_check(term_h, term_l, l, h);
    ASSERT_EQUAL(expected, result);

    h = 100;
    l = 100;
    expected = 1;
    result = win_size_check(term_h, term_l, l, h);
    ASSERT_EQUAL(expected, result);

    h = 99;
    l = 99;
    expected = 1;
    result = win_size_check(term_h, term_l, l, h);
    ASSERT_EQUAL(expected, result);

    h = 96;
    l = 98;
    expected = 0;
    result = win_size_check(term_h, term_l, l, h);
    ASSERT_EQUAL(expected, result);
    
    h = -1;
    l = -1;
    expected = 1;
    result = win_size_check(term_h, term_l, l, h);
    ASSERT_EQUAL(expected, result);
    
    h = 4;
    l = 4;
    expected = 0;
    result = win_size_check(term_h, term_l, l, h);
    ASSERT_EQUAL(expected, result);
}

CTEST(graphical_output, get_window_position_on_axis)
{
    int win_size = 10, sub_win_size = 24;
    int expected = win_size / 2 - sub_win_size / 2;
    int result = get_window_position_on_axis(sub_win_size, win_size);
    ASSERT_EQUAL(expected, result);
}
