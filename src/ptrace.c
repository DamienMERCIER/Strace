/*
** EPITECH PROJECT, 2021
** ptrace
** File description:
** ptrace
*/

#include "strace.h"

int error_syscall(struct user_regs_struct rgs, strace_info_s *strace)
{
    if ((WSTOPSIG(strace->w_status) == SIGTRAP ||
    WSTOPSIG(strace->w_status) == SIGSTOP) && WIFSTOPPED(strace->w_status)) {
        if (ptrace(PTRACE_GETREGS, strace->pid, NULL, &rgs))
            return (-1);
        return (1);
    }
    return (0);
}

int check_ptrace( struct user_regs_struct rgs, strace_info_s *strace)
{
    if (ptrace(PTRACE_GETREGS, strace->pid, NULL, &rgs))
        return (-1);
    if (ptrace(PTRACE_SINGLESTEP, strace->pid, 0, 0) == -1)
        return (-1);
    return (0);
}

void error_registers(struct user_regs_struct rgs, strace_info_s *strace)
{
    if (WIFSTOPPED(strace->w_status) && !WIFEXITED(strace->w_status)) {
        if (ptrace(PTRACE_GETREGS, strace->pid, NULL, &rgs))
            perror("error ptrace");
        if (rgs.orig_rax > 0 && rgs.orig_rax < 313)
            display_registers(rgs.orig_rax, rgs.rax, rgs, strace);
    }
}
