NAME = libft.a
CC = cc -Wall -Werror -Wextra
SRCS = ft_binarysearch.c \
		ft_bzero.c \
		ft_atol.c \
		ft_atoi.c \
		ft_memcpy.c \
		ft_strlcpy.c \
		ft_isdigit.c \
		ft_calloc.c \
		ft_isalpha.c \
		ft_strrchr.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_memchr.c \
		ft_tolower.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_memmove.c \
		ft_toupper.c \
		ft_memset.c \
		ft_strdup.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_strlen.c \
		ft_isalnum.c \
		ft_strmapi.c \
		ft_putendl_fd.c \
		ft_split.c \
		ft_putchar_fd.c \
		ft_putnbr_fd.c \
		ft_striteri.c \
		ft_itoa.c \
		ft_itoabase.c \
		ft_unsignitoabase.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_putstr_fd.c \
		ft_lstadd_back_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstmap_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c \
		ft_max.c \
		ft_min.c \

OBJ = $(SRCS:.c=.o)
SUBDIRS = get_next_line printf
SUBDIRSOBJ = $(foreach subdir, $(SUBDIRS), $(shell $(MAKE) -C $(subdir) -s list-objfiles))

all: $(NAME)

list-objfiles: $(OBJ) $(SUBDIRSOBJ)
	@echo $(OBJ) | tr ' ' '\n'
	@echo $(SUBDIRSOBJ) | tr ' ' '\n'

$(NAME): $(OBJ) subdir-objfiles 
	@for subdir in $(SUBDIRS); do \
		$(MAKE) -C $$subdir; \
		$(MAKE) -C $$subdir -s list-objfiles | while read objfile; do \
			if [ -f "$$subdir/$$objfile" ]; then \
				cp "$$subdir/$$objfile" .; \
			fi; \
		done; \
	done
	ar rcs $(NAME) $(OBJ) $(SUBDIRSOBJ)

subdir-objfiles:
	@for subdir in $(SUBDIRS); do \
		$(MAKE) -C $$subdir list-objfiles; \
	done

%.o:%.c
	$(CC) -c -o $@ $<

clean:
	@for subdir in $(SUBDIRS); do \
		$(MAKE) -C $$subdir clean; \
	done
	rm -rf $(OBJ) $(SUBDIRSOBJ)

fclean: clean
	@for subdir in $(SUBDIRS); do \
		$(MAKE) -C $$subdir fclean; \
	done
	rm -rf $(NAME) 

re: fclean all
	@for subdir in $(SUBDIRS); do \
		$(MAKE) -C $$subdir fclean; \
		$(MAKE) -C $$subdir; \
	done



.PHONY: all clean fclean re subdir-objfiles list-objfiles