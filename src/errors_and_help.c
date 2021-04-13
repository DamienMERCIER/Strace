/*
** EPITECH PROJECT, 2021
** errors
** File description:
** errors
*/
#include"strace.h"

int compare(char *str, char *str2)
{
    int i = 0;

    if (strlen(str) != strlen(str2))
        return (-1);
    while (str[i] && str2[i]) {
        if (str[i] != str2[i])
            return (-1);
        i++;
    }
    return (0);
}

void help(void)
{
    printf("%s", "Usage: ./strace [-s] [-p <pid>|<command>]\n");
}

int error(int ac)
{
    if (ac < MIN_ARGS )
        return (ERROR);
    else
        return (SUCCESS);
}

int manage_arg_errors (char **av, int opt)
{
    if (av[opt] == NULL) {
            printf("%s", "strace: option requires a valid argument\n");
            return (ERROR);
    }
    else if (compare(av[opt], "-p") == SUCCESS) {
        if (av[opt + 1] == NULL ) {
            printf("%s", "strace: option requires a valid argument");
            return (ERROR);
        }
        return (SUCCESS);
    }
    return (SUCCESS);
}