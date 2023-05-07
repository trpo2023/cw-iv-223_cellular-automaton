#include <stdio.h>

#include <Cellular_automaton/cellular_automaton.h>

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main()
{
    int h = 30, l = 60, ctdn = 2, ctdx = 3, ctnn = 3, ctnx = 3, env = 0;
    printf("Use custom settings (y/n)?");
    char yn = 'y';
    scanf("%c", &yn);
    if (yn == 'y') {
        printf("enter height: ");
        scanf("%d", &h);
        printf("enter length: ");
        scanf("%d", &l);
        printf("enter min cells to die: ");
        scanf("%d", &ctdn);
        printf("enter max cells to die: ");
        scanf("%d", &ctdx);
        printf("enter min cells to new cell: ");
        scanf("%d", &ctnn);
        printf("enter max cells to new cell: ");
        scanf("%d", &ctnx);
        printf("enter type of environmnt: ");
        scanf("%d", &env);
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
