NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

SRCS = main.c\
		search.c\
		redirects.c\
		token_extract/extract.c\
		token_extract/tokens.c\
		init.c\
		put_in_cmd.c\
		execve.c\
		env_init.c\
		prompt.c\
		built_in/cd.c\
		built_in/echo.c\
		built_in/env.c\
		built_in/export.c\
		built_in/pwd.c\
		built_in/unset.c\
		utils/fd_utils.c\
		utils/free.c\
		utils/open_file.c

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

test:
	norminette $(SRCS) minishell.h | grep Error
	./test.sh

.PHONY: all clean fclean re test
