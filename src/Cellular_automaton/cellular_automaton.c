#include "cellular_automaton.h"

#include <stdio.h>
#include <stdlib.h>


Cellular_automaton* create_automaton(
    int height,
    int length,
    int count_to_die_min,
    int count_to_die_max,
    int count_to_new_min,
    int count_to_new_max,
    int environment)//1 для окружения Фон Неймана 2 для вулфиша и все остальные для Мура
{
    Cellular_automaton* new_automaton
            = (Cellular_automaton*)malloc(sizeof(Cellular_automaton));
    new_automaton->length = length;
    new_automaton->height = height;
    new_automaton->count_to_die_min = count_to_die_min;
    new_automaton->count_to_die_max = count_to_die_max;
    new_automaton->count_to_new_min = count_to_new_min;
    new_automaton->count_to_new_max = count_to_new_max;
    new_automaton->environment = environment;
    if (!new_automaton) {
        return NULL;
    }

    new_automaton->matrix = (int**)malloc(height * sizeof(int*));
    if (!(new_automaton->matrix)) {
        free(new_automaton);
        return NULL;
    }
    for (int i = 0; i < height; i++) {
        new_automaton->matrix[i] = (int*)malloc(length * sizeof(int));
        if (!(new_automaton->matrix[i])) {
            free_automaton(new_automaton);
            return NULL;
        }
        for (int j = 0; j < length; j++) {
            new_automaton->matrix[i][j] = 0;
        }
    }

    return new_automaton;
}

Cellular_automaton* create_simple_automaton(int h, int l)
{
    Cellular_automaton* new_automaton
            = (Cellular_automaton*)malloc(sizeof(Cellular_automaton));
    new_automaton->length = l;
    new_automaton->height = h;
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
        for (int j = 0; j < l; j++) {
            new_automaton->matrix[i][j] = 0;
        }
    }

    return new_automaton;
}

Cellular_automaton* copy_automaton(Cellular_automaton* cell)
{
    Cellular_automaton* new_automaton
            = (Cellular_automaton*)malloc(sizeof(Cellular_automaton));
    new_automaton->length = cell->length;
    new_automaton->height = cell->height;
    new_automaton->count_to_die_min = cell->count_to_die_min;
    new_automaton->count_to_die_max = cell->count_to_die_max;
    new_automaton->count_to_new_min = cell->count_to_new_min;
    new_automaton->count_to_new_max = cell->count_to_new_max;
    new_automaton->environment = cell->environment;
    if (!new_automaton) {
        return NULL;
    }

    new_automaton->matrix = (int**)malloc(cell->height * sizeof(int*));
    if (!(new_automaton->matrix)) {
        free(new_automaton);
        return NULL;
    }
    for (int i = 0; i < cell->height; i++) {
        new_automaton->matrix[i] = (int*)malloc(cell->length * sizeof(int));
        if (!(new_automaton->matrix[i])) {
            free_automaton(new_automaton);
            return NULL;
        }
        for (int j = 0; j < cell->length; j++) {
            new_automaton->matrix[i][j] = cell->matrix[i][j];
        }
    }

    return new_automaton;
}

int alive_or_dead(int x, int y, Cellular_automaton* cell)
{
    int c_next;
    if (cell->environment == 1) {
        c_next = Von_Neumann(x, y, cell);
    } else {
        if (cell->environment == 2)
            c_next = Wolfish(x, y, cell);
        else
            c_next = Moore(x, y, cell);
    }
    if (cell->matrix[x][y] == 0) {
        if (c_next >= cell->count_to_new_min
            && c_next <= cell->count_to_new_max)
            return 1;
        else
            return 0;
    } else {
        if (c_next >= cell->count_to_die_min
            && c_next <= cell->count_to_die_max)
            return 1;
        else
            return 0;
    }
}

Cellular_automaton* next_frame(Cellular_automaton* cell)
{
    Cellular_automaton* tmp = copy_automaton(cell);
    for (int i = 0; i < cell->height; i++) {
        for (int j = 0; j < cell->length; j++) {
            cell->matrix[i][j] = alive_or_dead(i, j, tmp);
        }
    }
    free_automaton(tmp);
    return cell;
}

int Moore(int x, int y, Cellular_automaton* cell)
{
    int c_next = 0;
    if (x - 1 >= 0) {
        if (y - 1 >= 0)
            c_next += cell->matrix[x - 1][y - 1];
        c_next += cell->matrix[x - 1][y];
        if (y + 1 < cell->length)
            c_next += cell->matrix[x - 1][y + 1];
    }
    if (y - 1 >= 0)
        c_next += cell->matrix[x][y - 1];
    if (y + 1 < cell->length)
        c_next += cell->matrix[x][y + 1];
    if (x + 1 < cell->height) {
        if (y - 1 >= 0)
            c_next += cell->matrix[x + 1][y - 1];
        c_next += cell->matrix[x + 1][y];
        if (y + 1 < cell->length)
            c_next += cell->matrix[x + 1][y + 1];
    }
    return c_next;
}

int Von_Neumann(int x, int y, Cellular_automaton* cell)
{
    int c_next = 0;
    if (x - 1 >= 0)
        c_next += cell->matrix[x - 1][y];
    if (y - 1 >= 0)
        c_next += cell->matrix[x][y - 1];
    if (y + 1 < cell->length)
        c_next += cell->matrix[x][y + 1];
    if (x + 1 < cell->height)
        c_next += cell->matrix[x + 1][y];
    return c_next;
}

int Wolfish(int x, int y, Cellular_automaton* cell)
{
    int c_next = 0;
    if (x - 1 >= 0) {
        if (y - 1 >= 0)
            c_next += cell->matrix[x - 1][y - 1];
        if (y + 1 < cell->length)
            c_next += cell->matrix[x - 1][y + 1];
    }
    if (x + 1 < cell->height) {
        if (y - 1 >= 0)
            c_next += cell->matrix[x + 1][y - 1];
        if (y + 1 < cell->length)
            c_next += cell->matrix[x + 1][y + 1];
    }
    return c_next;
}

void free_automaton(Cellular_automaton* to_del)
{
    if (to_del != NULL) {
        if (to_del->matrix != NULL) {
            for (int i = 0; i < to_del->height; i++) {
                if (to_del->matrix[i] != NULL)
                    free(to_del->matrix[i]);
            }
            free(to_del->matrix);
        }
        free(to_del);
    }
}
