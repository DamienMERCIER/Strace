/*
** EPITECH PROJECT, 2021
** display
** File description:
** display
*/

#include "strace.h"

void print_register(char *name, int nb_args, unsigned int reg,
                    strace_info_s *strace, int type)
{
    if (nb_args > 0 && type == 2)
            printf("0x%x", reg);
    else if (nb_args > 0 && type == 0)
            printf(", 0x%x", reg);
    if (nb_args > 0 && type == 1) {
        if (!strace->flag_type && compare(name, "write") == 0)
            printf(", %d", reg);
        else
            printf(", 0x%x", reg);
    }
}

void print_all_register(char *name, int count, struct user_regs_struct rgs,
                    strace_info_s *strace)
{
    print_register(name, count, (unsigned int)rgs.rdi, strace, 2);
    count--;
    print_register(name, count, (unsigned int)rgs.rsi, strace, 0);
    count--;
    print_register(name, count, (unsigned int)rgs.rdx, strace, 1);
    count--;
    print_register(name, count, (unsigned int)rgs.rcx, strace, 0);
    count--;
    print_register(name, count, (unsigned int)rgs.r8, strace, 0);
    count--;
    print_register(name, count, (unsigned int)rgs.r9, strace, 0);
}

void display_registers(unsigned sysnum, unsigned retval,
                    struct user_regs_struct rgs, strace_info_s *strace)
{
    printf("%s(", my_syscall[(int)sysnum].name);
    if (my_syscall[sysnum].nb_params != 0)
        print_all_register(my_syscall[(int)sysnum].name,
                    my_syscall[sysnum].nb_params, rgs, strace);
    printf(") = ");
    if (retval) {
        if (!strace->flag_type
        && strcmp(my_syscall[(int)sysnum].name, "write") == 0)
            printf("%d\n", (unsigned int)retval);
        else
            printf("0x%x\n", (unsigned int)retval);
    } else
        printf("?\n");
}