#include "cellular_automaton.h"
#include <stdlib.h>

Cellular_automaton* create_simple_automaton(int l, int h)
{
    Cellular_automaton* new_automaton
            = (Cellular_automaton*)malloc(sizeof(Cellular_automaton));
    new_automaton->length = l;
    new_automaton->hight = h;
    new_automaton->count_to_die_min = 2;
    new_automaton->count_to_die_max = 3;
    new_automaton->count_to_new_min = 3;
    new_automaton->count_to_new_max = 3;
    new_automaton->environment = 0;
    if (!new_automaton) {
        return NULL;
    }

    new_automaton->matrix = (int**)malloc(h * sizeof(int*));
    if (!(new_automaton->matrix)) {
        free(new_automaton);
        return NULL;
    }
    for (int i = 0; i < h; i++) {
        new_automaton->matrix[i] = (int*)malloc(l * sizeof(int));
        if (!(new_automaton->matrix[i])) {
            free_automaton(new_automaton);
            return NULL;
        }
        for(int j = 0; j<l; j++)
        {
           new_automaton->matrix[i][j] = 0;
        }
    }

    return new_automaton;
}

void free_automaton(Cellular_automaton* to_del)
{
    if (to_del != NULL) {
        if (to_del->matrix != NULL) {
            for (int i = 0; i < to_del->hight; i++) {
                if (to_del->matrix[i] != NULL)
                    free(to_del->matrix[i]);
            }
            free(to_del->matrix);
        }
        free(to_del);
    }
}
