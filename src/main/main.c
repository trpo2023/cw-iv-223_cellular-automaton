#include <stdio.h>

#include <Cellular_automaton/cellular_automaton.h>
#include <Input/input_user_interface.h>

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (check_num_of_arguments(argc)) {
        printf("%sError:%s too few arguments\n\n", RED, RESET);
        printf("usage: ./bin/cellular-automaton %s-<environment> ", PURPLE);
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
    time_t t;
    int n = 10;
    printf("enter number of frames: ");
    scanf("%d", &n);
    srand((unsigned)time(&t));
    for (int i = 0; i < cell->height; i++) {
        for (int j = 0; j < cell->length; j++) {
            cell->matrix[i][j] = rand() % 2;
            printf("%d ", cell->matrix[i][j]);
        }
        printf("\n");
    }
    usleep(100);
    for (int k = 0; k < n; k++) {
        usleep(200000);
        system("clear");
        printf("\n");
        cell = next_frame(cell);

        for (int i = 0; i < cell->height; i++) {
            for (int j = 0; j < cell->length; j++) {
                if (cell->matrix[i][j])
                    printf("\033[41m%c\033[0m", ' ');
                else
                    printf("\033[37m%c\033[0m", ' ');
            }
            printf("\n");
        }
    }
    free_automaton(cell);
    return 0;
}
