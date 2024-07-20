# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/06 16:08:12 by mzhuang           #+#    #+#              #
#    Updated: 2024/07/20 18:19:24 by mzhuang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= pipex.c
# SRC2 		= stack_util.c ft_mergesort.c parse_checks.c freeinput.c sortstacks.c pushfunctions.c \
# 				rotatefunctions.c revrotatefunctions.c swapfunctions.c  stackfunctions.c \
# 				parse_input.c sortstacks2.c 
NAME 		= push_swap
OBJ1		= ${SRC:.c=.o}
# OBJ2		= ${SRC2:.c=.o}
LIBDIR		= libft
LIBNAME		= libft/libft.a
LIBINC 		= -L ./libft -lft
CC			= cc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -g
# B_NAME	= checker
# B_SRC	= checker_bonus.c
# B_OBJ	= ${B_SRC:.c=.o}


all:		$(NAME)

$(LIBNAME):
	$(MAKE) -C $(LIBDIR)

$(NAME):	${OBJ1} $(LIBNAME)
			${CC} ${CFLAGS} ${OBJ1} -o $@ ${LIBINC}

%.o : %.c
			${CC} ${CFLAGS} -c -I${LIBDIR} -o $@ $< 

clean:
			${RM} ${OBJ1}
			${MAKE} -C $(LIBDIR) clean


fclean:		clean		
			${RM} $(NAME)
			${MAKE} -C $(LIBDIR) fclean


re:			fclean all


.PHONY:		all clean fclean re bonus
