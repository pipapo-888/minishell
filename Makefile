NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c\
		search.c\
		space_tab_split.c
OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ -lreadline $(LIBFT)

$(LIBFT):
	make -C libft all

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
