#pragma once

#define LIVE_CELL 1

#include <ncurses.h>

_Bool win_size_check(int term_h, int term_l, int l, int h);
int get_window_position_on_axis(int sub_win_size, int win_size);
WINDOW* window_init(int term_h, int term_l, int l, int h);
void print_legend(
        int term_h,
        int min_to_new,
        int max_to_new,
        int min_to_die,
        int max_to_die);
void print_matrix(WINDOW* win, Cellular_automaton* cell);
