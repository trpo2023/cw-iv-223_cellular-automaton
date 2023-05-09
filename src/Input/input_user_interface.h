#pragma once

// для check_num_of_arguments()
#define RIGHT_NUM_OF_ARGUMENTS 8

// для cell_rules_check()
#define MIN_TO_NEW_IND 2
#define MAX_TO_NEW_IND 3
#define MIN_TO_DIE_IND 4
#define MAX_TO_DIE_IND 5
#define NUMS "0123456789"

// для цветного вывода в коммандную строку
#define YELLOW "\033[1;33m"
#define RED "\033[1;31m"
#define PURPLE "\033[35m"
#define GREEN "\033[32m"
#define BLUE "\033[36m"
#define RESET "\033[0m"

_Bool check_num_of_arguments(int argc);
int get_environmnt(char* argv[]);
int cell_rules_check(int rule_ind, int env, char* argv[]);
int get_error_code(
        int env, int ctnn, int ctnx, int ctdn, int ctdx, int l, int h);
void print_error(int error_code);
