NAME = minishell
CC = cc
CFLAGS = -g -Wall -Wextra -Werror

SRCS = main.c\
		execve.c\
		execve_utils.c\
		prompt.c\
		signal.c\
		cmd_init/extract_option.c\
		cmd_init/extract_word.c\
		cmd_init/heredoc.c\
		cmd_init/tokens.c\
		cmd_init/cmd_setup.c\
		cmd_init/put_in_option.c\
		cmd_init/put_in_word.c\
		cmd_init/cmd_utils.c\
		cmd_init/expand_single.c\
		cmd_init/expand_variables.c\
		env/env_to_array.c\
		env/env_init.c\
		env/env_utils.c\
		env/env_utils2.c\
		built_in/cd.c\
		built_in/echo.c\
		built_in/env.c\
		built_in/export.c\
		built_in/export_2.c\
		built_in/pwd.c\
		built_in/unset.c\
		built_in/exit.c\
		utils/fd_utils.c\
		utils/free.c\
		utils/search.c\
		utils/redirects.c\
		utils/open_file.c\
		utils/set_exit_status.c\
		utils/char_utils.c\
		utils/space_tab_split.c\
		utils/prompt_utils.c\
		utils/llong_check.c\

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
