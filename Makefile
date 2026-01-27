NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

SRCS = main.c\
		execve.c\
		prompt.c\
		cmd_init/extract_option.c\
		cmd_init/extract_word.c\
		cmd_init/heredoc.c\
		cmd_init/tokens.c\
		cmd_init/cmd_setup.c\
		cmd_init/put_in_cmd.c\
		cmd_init/cmd_utils.c\
		env/env_to_array.c\
		env/env_init.c\
		env/env_utils.c\
		env/env_utils2.c\
		env/expand_single.c\
		env/expand_variables.c\
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
		utils/expand_variables.c\
		utils/set_exit_status.c\
		utils/char_utils.c\

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
