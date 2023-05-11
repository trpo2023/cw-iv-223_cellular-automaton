#include <ncurses.h>

#include <Cellular_automaton/cellular_automaton.h>
#include <Screen/graphical-output.h>

_Bool win_size_check(int term_h, int term_l, int l, int h)
{
    if (term_h < h + 2) // учитываем верхнюю и нижнюю строку
        return 1;
    if (term_l < l)
        return 1;
    return 0; // размеры соответствуют
}

int get_window_position_on_axis(int sub_win_size, int win_size)
{
    return win_size / 2 - sub_win_size / 2;
}

WINDOW* window_init(int term_h, int term_l, int l, int h)
{
    int win_pos_y = get_window_position_on_axis(h, term_h);
    int win_pos_x = get_window_position_on_axis(l, term_l);

    WINDOW* win = newwin(h, l, win_pos_y, win_pos_x); // +2 из-за рамки
    keypad(win, true); // подключаем возможность считывать специальные клавиши
    return win;
}

void print_legend(
        int term_h,
        int min_to_new,
        int max_to_new,
        int min_to_die,
        int max_to_die)
{
    printw(" cellular automaton\t");
    printw("rules_to_new [%d, %d] ", min_to_new, max_to_new);
    printw("rules_to_die [%d, %d] ", min_to_die, max_to_die);
    mvprintw(term_h - 1, 1, "<ESC> - exit");
    refresh();
}

void print_matrix(WINDOW* win, Cellular_automaton* cell)
{
    wclear(win);
    wattron(win, COLOR_PAIR(LIVE_CELL));
    for (int i = 0; i < cell->length; i++)
        for (int j = 0; j < cell->height; j++) {
            if (cell->matrix[j][i])
                mvwaddch(win, j + 1, i + 1, '@');
        }
    wattroff(win, COLOR_PAIR(LIVE_CELL));
    box(win, 0, 0);
    wrefresh(win);
}
