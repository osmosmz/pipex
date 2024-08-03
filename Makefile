# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/06 16:08:12 by mzhuang           #+#    #+#              #
#    Updated: 2024/08/03 17:21:35 by mzhuang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= pipex.c
SRC2 		= parsecommand.c cleanup.c

NAME 		= pipex
OBJ1		= ${SRC:.c=.o}
OBJ2		= ${SRC2:.c=.o}
LIBDIR		= libft
LIBNAME		= libft/libft.a
LIBINC 		= -L ./libft -lft
CC			= cc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -g
# B_NAME	= pipex_bonus
# B_SRC	= pipex_bonus.c
# B_OBJ	= ${B_SRC:.c=.o}


all:		$(NAME)

$(LIBNAME):
	$(MAKE) -C $(LIBDIR)

$(NAME):	${OBJ1} ${OBJ2} $(LIBNAME)
			${CC} ${CFLAGS} ${OBJ1} ${OBJ2} -o $@ ${LIBINC}

%.o : %.c
			${CC} ${CFLAGS} -c -I${LIBDIR} -o $@ $< 

clean:
			${RM} ${OBJ1} ${OBJ2}
			${MAKE} -C $(LIBDIR) clean


fclean:		clean		
			${RM} $(NAME)
			${MAKE} -C $(LIBDIR) fclean


re:			fclean all


.PHONY:		all clean fclean re bonus
