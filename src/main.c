/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/
#include "strace.h"

int my_strace(strace_info_s *strace)
{
    struct user_regs_struct rgs;

    waitpid(strace->pid, &strace->w_status, 0);
    while ( WIFSTOPPED(strace->w_status) && !WIFEXITED(strace->w_status)) {
        if (check_ptrace(rgs, strace) == -1)
            perror("error ptrace");
        waitpid(strace->pid, &strace->w_status, 0);
        error_registers(rgs, strace);
    }
    printf("+++ exited with 0 +++\n");
    return (0);
}

int main(int ac, char **av, char **envp)
{
    strace_info_s strace;

    strace.flag_type = 1;
    char **bin = av + 1;

    if (error(ac) == ERROR) {
        help();
        return (ERROR);
    }
    if (manage_arg_errors(av, (2 + compare(av[1], "-s"))) == ERROR)
        return (ERROR);
    if (compare(av[1], "-s") == SUCCESS) {
        strace.flag_type = 0;
        bin = av + 2;
    }
    strace.pid = fork();
    if (strace.pid == 0) {
        if (create_pid(ac - 1, bin, envp) == -1)
            return (84);
        return (SUCCESS);
    }
    return (my_strace(&strace));
}
