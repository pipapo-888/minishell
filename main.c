#include "./minishell.h"

volatile sig_atomic_t	g_sig = 0;

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
