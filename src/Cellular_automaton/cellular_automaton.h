#pragma once

typedef struct {
    int length;
    int hight;
    int** matrix;
    int count_to_die_min;
    int count_to_die_max;
    int count_to_new_min;
    int count_to_new_max;
    int environment;
    
} Cellular_automaton;

Cellular_automaton* create_simple_automaton(int l, int h);
void free_automaton(Cellular_automaton* to_del);
