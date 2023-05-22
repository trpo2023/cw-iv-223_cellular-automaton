#include <ncurses.h>
#include <Interaction/interaction.h>

_Bool is_pause_check(_Bool is_pause, _Bool is_edit, char key)
{
    if (!is_edit) {
        if (key == 'p' || key == ' ') {
            if (is_pause)
                return 0;
            return 1;
        }
    }
    return is_pause;
}

void print_mode(
        WINDOW* win, int term_l, int term_h, _Bool is_pause, _Bool is_edit)
{
    wattron(win, COLOR_PAIR(MESSANGE));
    if (is_pause) {
        if (is_edit) {
            mvprintw(0, term_l - 12, "[edit_mode]");
            mvprintw(
                    term_h - 1,
                    term_l - 44,
                    "<c> - clear field   <s> - cell state change");
        } else
            mvprintw(0, term_l - 12, "    [PAUSE]");
    } else {
        mvprintw(0, term_l - 12, "     [PLAY]");
        mvprintw(
                term_h - 1,
                term_l - 40,
                "                                       ");
    }
    refresh();
}

_Bool is_exit_check(char key)
{
    if (key == 27)
        return 1;
    return 0;
}

_Bool is_edit_mode_check(_Bool is_pause, _Bool is_edit, char key)
{
    if (key == 'e' && is_pause) {
        if (is_edit)
            return 0;
        return 1;
    }
    return is_edit;
}

coordinates cursor_movement(int key, coordinates cur, int win_h, int win_l)
{
    if (key == KEY_DOWN && cur.y < win_h - 3)
        cur.y++;
    if (key == KEY_UP && cur.y > 0)
        cur.y--;
    if (key == KEY_RIGHT && cur.x < win_l - 3)
        cur.x++;
    if (key == KEY_LEFT && cur.x > 0)
        cur.x--;
    return cur;
}

int** cell_state_change(int key, coordinates cur, int** matrix, WINDOW* win)
{
    if (key == 's') {
        if (matrix[cur.y][cur.x])
            matrix[cur.y][cur.x] = 0;
        else
            matrix[cur.y][cur.x] = 1;
    }
    if (matrix[cur.y][cur.x])
        wattron(win, COLOR_PAIR(LIVE_CELL_BACK));
    mvwprintw(win, cur.y + 1, cur.x + 1, "0");
    wattroff(win, COLOR_PAIR(LIVE_CELL_BACK));
    wrefresh(win);
    return matrix;
}

int** clear_field(char key, int** matrix, int length, int height)
{
    if (key == 'c')
        for (int i = 0; i < length; i++)
            for (int j = 0; j < height; j++)
                matrix[j][i] = 0;
    return matrix;
}
