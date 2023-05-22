#include "input_user_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Bool check_num_of_arguments(int argc)
{
    if (argc != RIGHT_NUM_OF_ARGUMENTS)
        return -1; // количество переданных aргументов не
    return 0; // соотв. необходимому
}

int get_environmnt(char* argv[])
{
    if (!strcmp(argv[1], "-von_neumann\0"))
        return 1;
    if (!strcmp(argv[1], "-wolfish\0"))
        return 2;
    if (!strcmp(argv[1], "-moore\0"))
        return 3;
    return 0; // локальная окрестность
} // введена не верно

int cell_rules_check(int rule_ind, int env, char* argv[])
{
    int size_of_num
            = strspn(argv[rule_ind], NUMS); // число символов, соотв. цифрам
    int full_size = strlen(argv[rule_ind]);

    if (size_of_num != full_size)
        return -1; // введено не число

    int rule_range = atoi(argv[rule_ind]);
    if (env < 3) // для окрестностей von_neumann и wolfish
    {
        if (rule_range > 4 || rule_range < 0)
            return -1;
    } else // для окрестности moore
            if (rule_range > 8 || rule_range < 0)
        return -1;
    return rule_range;
}

int get_error_code(
        int env, int ctnn, int ctnx, int ctdn, int ctdx, int l, int h)
{
    if (env == 0)
        return 1; // окрестность введена не верно
    if (ctnn == -1)
        return 2; // нижняя граница правил рождения введена не верно
    if (ctnx == -1)
        return 3; // нижняя граница правил смерти введена не верно
    if (ctdn == -1)
        return 4; // верхняя граница правил рождения введена не верно
    if (ctdx == -1)
        return 5; // верхняя граница правил смерти введена не верно
    if (l == 0)
        return 6; // ширина введена не верно
    if (h == 0)
        return 7; // высота введена не верно
    return 0;     // завершение без ошибок
}

void print_error(int error_code)
{
    switch (error_code) {
    case 1:
        printf("%sError:%s got wrong %s-<environment>%s\n\n",
               RED,
               RESET,
               PURPLE,
               RESET);
        break;
    case 2:
        printf("%sError:%s got wrong %s<min_to_new>%s\n\n",
               RED,
               RESET,
               PURPLE,
               RESET);
        break;
    case 3:
        printf("%sError:%s got wrong %s<max_to_new>%s\n\n",
               RED,
               RESET,
               PURPLE,
               RESET);
        break;
    case 4:
        printf("%sError:%s got wrong %s<min_to_die>%s\n\n",
               RED,
               RESET,
               PURPLE,
               RESET);
        break;
    case 5:
        printf("%sError:%s got wrong %s<max_to_die>%s\n\n",
               RED,
               RESET,
               PURPLE,
               RESET);
        break;
    case 6:
        printf("%sError:%s got wrong %s<length>%s\n\n",
               RED,
               RESET,
               PURPLE,
               RESET);
        break;
    case 7:
        printf("%sError:%s got wrong %s<height>%s\n\n",
               RED,
               RESET,
               PURPLE,
               RESET);
        break;
    }
    // вывод допустимых значений при разных ошибках
    if (error_code == 1) {
        printf("  <environment>%s allowed:   ", RESET);
        printf("%s-moore ", BLUE);
        printf("-von_neumann ");
        printf("-wolfish%s\n\n", RESET);
    }
    if (error_code > 1 && error_code < 6) {
        printf("for %s-von_neumann%s and %s-wolfish%s environments:\n",
               BLUE,
               RESET,
               BLUE,
               RESET);
        printf("   %s<min_to_new> <max_to_new> <min_to_die> <max_to_die>%s "
               "allowed:   ",
               PURPLE,
               RESET);
        printf("nums from %s0%s to %s4%s\n\n", GREEN, RESET, GREEN, RESET);
        printf("for %s-moore%s environment:\n", BLUE, RESET);
        printf("   %s<min_to_new> <max_to_new> <min_to_die> <max_to_die>%s "
               "allowed:   ",
               PURPLE,
               RESET);
        printf("nums from %s0%s to %s8%s\n\n", GREEN, RESET, GREEN, RESET);
    }
    if (error_code > 5) {
        printf("  %s<width> <height>%s allowed:   ", PURPLE, RESET);
        printf("nums > %s0%s\n\n", GREEN, RESET);
    }
}
