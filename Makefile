##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

SRC		=		src/main.c	\
				src/errors_and_help.c	\
				src/display.c \
				src/pid.c	\
				src/ptrace.c

NAME	=		strace

CFLAGS	=		-Wall -Wextra -I include

OBJ		=		$(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean re fclean