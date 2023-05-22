#pragma once

typedef struct {
    int length;
    int height;
    int** matrix;
    int count_to_die_min;
    int count_to_die_max;
    int count_to_new_min;
    int count_to_new_max;
    int environment;

} Cellular_automaton;

Cellular_automaton* create_automaton(
        int length,
        int height,
        int count_to_die_min,
        int count_to_die_max,
        int count_to_new_min,
        int count_to_new_max,
        int environment);
Cellular_automaton* create_simple_automaton(int l, int h);
Cellular_automaton* copy_automaton(Cellular_automaton* cell);
int alive_or_dead(int x, int y, Cellular_automaton* cell);
void change_state(int x, int y, Cellular_automaton* cell);
Cellular_automaton* next_frame(Cellular_automaton* cell);
int Moore(int x, int y, Cellular_automaton* cell);
int Von_Neumann(int x, int y, Cellular_automaton* cell);
int Wolfish(int x, int y, Cellular_automaton* cell);
void free_automaton(Cellular_automaton* to_del);
