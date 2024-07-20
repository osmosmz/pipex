DIRLIB		= ../
SRC			= ft_printf.c printargs.c parser.c printspace.c printchar.c \
				printint.c printunsignedint.c printintutil.c  printstring.c
OBJ		= ${SRC:.c=.o}
NAME		= libftprintf.a
CC			= cc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -g

all:		$(NAME)

$(NAME):	${OBJ} 

%.o : %.c
			${CC} ${CFLAGS} -c -I${DIRLIB} -o $@ $< 

list-objfiles:
	@echo $(OBJ) | tr ' ' '\n'
clean:
			${RM} ${OBJ} 

fclean:		clean		

re:			fclean all

.PHONY:		all clean fclean re 
