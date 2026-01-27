#include "./minishell.h"

void	handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int ac, char **av, char **envp)
{
	char	*program_name;
	t_data	data;

	env_init(&data, envp);
	(void)ac;
	(void)av;
	(void)program_name;
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
