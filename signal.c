#include "minishell.h"

void	handler(int sig)
{
	(void)sig;
	g_sig = SIG_INT_FAIL;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	heredoc_handler(int sig)
{
	(void)sig;
	g_sig = SIG_INT_FAIL;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}
