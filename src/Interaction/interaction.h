#pragma once

#define MESSANGE 2
#define LIVE_CELL_BACK 3

typedef struct {
    int x;
    int y;
} coordinates;

_Bool is_pause_check(_Bool is_pause, _Bool is_edit, char key);
void print_mode(
        WINDOW* win, int temp_l, int term_h, _Bool is_pause, _Bool is_edit);
_Bool is_exit_check(char key);
_Bool is_edit_mode_check(_Bool is_pause, _Bool is_edit, char key);
coordinates cursor_movement(int key, coordinates cur, int win_h, int win_l);
int** cell_state_change(int key, coordinates cur, int** matrix, WINDOW* win);
int** clear_field(char key, int** matrix, int length, int height);
