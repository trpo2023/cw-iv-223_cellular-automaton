#include <stdio.h>

#include <Cellular_automaton/cellular_automaton.h>
#include <Input/input_user_interface.h>
#include <Screen/graphical-output.h>
#include <Interaction/interaction.h>

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (check_num_of_arguments(argc)) {
        printf("%sError:%s too few arguments\n\n", RED, RESET);
        printf("  usage: ./bin/cellular-automaton %s-<environment> ", PURPLE);
        printf("<min_to_new> <max_to_new> <min_to_die> ");
        printf("<max_to_die> <length> <height>\n\n");
        return 1;
    }

    int env = get_environmnt(argv);

    int ctnn = cell_rules_check(MIN_TO_NEW_IND, env, argv);
    int ctnx = cell_rules_check(MAX_TO_NEW_IND, env, argv);
    int ctdn = cell_rules_check(MIN_TO_DIE_IND, env, argv);
    int ctdx = cell_rules_check(MAX_TO_DIE_IND, env, argv);

    int l = atoi(argv[6]);
    int h = atoi(argv[7]);

    int error_code = get_error_code(env, ctnn, ctnx, ctdn, ctdx, l, h);
    if (error_code) {
        print_error(error_code);
        return 1;
    }

    Cellular_automaton* cell
            = create_automaton(h, l, ctdn, ctdx, ctnn, ctnx, env);

    int win_l = l + 2;
    int win_h = h + 2;
    int term_l, term_h;

    initscr();
    getmaxyx(stdscr, term_h, term_l); // получаем размер терминала

    if (win_size_check(term_h, term_l, win_l, win_h)) {
        endwin();
        printf("%sError:%s field size exceeds terminal size\n\n", RED, RESET);
        printf("  maximum allowable %s<length>%s: %s%d%s\n\n",
               PURPLE,
               RESET,
               GREEN,
               term_l - 2,
               RESET);
        printf("  maximum allowable %s<width>%s: %s%d%s\n\n",
               PURPLE,
               RESET,
               GREEN,
               term_h - 4,
               RESET);
        return 1;
    }

    noecho();     // не отображать ввод с клавиатуры
    halfdelay(5); // оживание ввода с клавиатуры определенное время, если ничего
                  // не было введено за это время возвращает -1
    curs_set(0); // убирает курсор терминала
    start_color();
    init_pair(LIVE_CELL, COLOR_GREEN, COLOR_GREEN);
    init_pair(MESSANGE, COLOR_MAGENTA, COLOR_BLACK);

    WINDOW* win = window_init(term_h, term_l, win_l, win_h);
    print_legend(term_h, ctnn, ctnx, ctdn, ctdx);

    srand(time(NULL));
    for (int i = 0; i < cell->height; i++)
        for (int j = 0; j < cell->length; j++)
            cell->matrix[i][j] = rand() % 2;

    char key;
    _Bool is_pause= 1; //нахождение в паузе
    _Bool is_edit= 0; //активен ли режим редактирования поля 
    while (1) // 27= ESC_key
    {
    	key= getch();
    	is_pause= is_pause_check(is_pause, key);
    	if(is_exit_check(key))
    		break;
    	is_edit= is_edit_mode_check(is_pause, is_edit, key);
    	if(is_pause)
    		print_pause(stdscr, term_l);
    	else
        	cell = next_frame(cell);
        print_matrix(win, cell);
    }

    free_automaton(cell);
    endwin();
    return 0;
}
