NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

SRCS = main.c\
		execve.c\
		env_init.c\
		prompt.c\
		cmd_init/extract.c\
		cmd_init/tokens.c\
		cmd_init/cmd_setup.c\
		cmd_init/put_in_cmd.c\
		built_in/cd.c\
		built_in/echo.c\
		built_in/env.c\
		built_in/export.c\
		built_in/pwd.c\
		built_in/unset.c\
		utils/fd_utils.c\
		utils/free.c\
		utils/search.c\
		utils/redirects.c\
		utils/open_file.c\
		utils/expand_variables.c

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
