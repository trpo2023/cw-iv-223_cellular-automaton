#include <ncurses.h>
#include <Interaction/interaction.h>

_Bool is_pause_check(_Bool is_pause, char key)
{
	if(key== 'p' || key== ' ')
	{
		if(is_pause)
			return 0;
		return 1;
	}
	return is_pause;
}

void print_pause(WINDOW* win, int temp_l)
{
	wattron(win, COLOR_PAIR(MESSANGE));
	mvprintw(0, temp_l-8 , "[PAUSE]");
	wattroff(win, COLOR_PAIR(MESSANGE));
	refresh();
}

_Bool is_exit_check(char key)
{
	if(key== 27)
		return 1;
	return 0;
}

_Bool is_edit_mode_check(_Bool is_pause, _Bool is_edit, char key)
{
	if(key== 'e' && is_pause)
	{
		if(is_edit)
			return 0;
		return 1;
	}
	return is_edit;
}
	
