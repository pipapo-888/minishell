NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

SRCS = main.c\
		search.c\
		redirects.c\
		extract.c\
		tokens.c\
		init.c\
		free.c\
		env_init.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) -lreadline

$(LIBFT):
	make -C libft all

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

test: all
	./test.sh

.PHONY: all clean fclean re test
