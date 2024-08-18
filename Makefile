# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/06 16:08:12 by mzhuang           #+#    #+#              #
#    Updated: 2024/08/18 23:13:59 by mzhuang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= pipex.c heredoc.c parsecommand.c cleanup.c
NAME 		= pipex
OBJ		= ${SRC:.c=.o}
LIBDIR		= libft
LIBNAME		= libft/libft.a
LIBINC 		= -L ./libft -lft
CC			= cc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -g
LIBOBJ = $((MAKE) -C $(LIBDIR) -s list-objfiles)



all:		$(NAME)

bonus: 	$(NAME)


$(LIBNAME): 
	$(MAKE) -C $(LIBDIR)

$(NAME):	${OBJ} $(LIBNAME)
			${CC} ${CFLAGS} ${OBJ} -o $@ ${LIBINC}

%.o : %.c
			${CC} ${CFLAGS} -c -I${LIBDIR} -o $@ $< 

clean:
			${RM} ${OBJ}
			${MAKE} -C $(LIBDIR) clean


fclean:		clean		
			${RM} $(NAME)
			${MAKE} -C $(LIBDIR) fclean

re:			fclean all

.PHONY:		all clean fclean re bonus
