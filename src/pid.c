/*
** EPITECH PROJECT, 2021
** pid
** File description:
** pid
*/
#include "strace.h"

int create_pid(int ac, char **av, char **envp)
{
    char *bin[ac + 1];

    memcpy(bin, av, ac * sizeof(char *));
    bin[ac] = NULL;
    ptrace(PTRACE_TRACEME);
    kill(getpid(), SIGSTOP);
    return execve(bin[0], bin, envp);
}