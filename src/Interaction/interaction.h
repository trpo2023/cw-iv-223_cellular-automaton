#pragma once
#define MESSANGE 2

_Bool is_pause_check(_Bool is_pause, char key);
void print_pause(WINDOW* win, int temp_l);
_Bool is_exit_check(char key);
_Bool is_edit_mode_check(_Bool is_pause, _Bool is_edit, char key);
