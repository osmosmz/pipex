CC = cc -Wall -Werror -Wextra -g 
SRCS = get_next_line.c get_next_line_utils.c   
OBJ = $(SRCS:.c=.o)
HEADER = get_next_line.h


all: $(OBJ)
%.o:%.c
	$(CC) -c -o $@ $<
list-objfiles:
	@echo $(OBJ) | tr ' ' '\n'
clean:
	rm -rf $(OBJ) 
fclean: clean 
re: fclean all

.PHONY:			all clean fclean re 
