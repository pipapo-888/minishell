#include "./minishell.h"

void	handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// set_exit_status(data.env, SIG_INT_FAIL);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac != 1 && av[1] != NULL)
	{
		ft_putstr_fd("Usage: ./minishell\n", 2);
		return (1);
	}
	env_init(&data, envp);
	data.cmd = NULL;
	data.input = NULL;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		prompt(data);
	}
	return (0);
}
