#include "./minishell.h"

static int	check_early_return(t_data *data, char **env)
{
	if (g_sig == SIG_INT_FAIL)
	{
		set_exit_status(data->env, g_sig);
		g_sig = 0;
		free_exit(data, env, DONT_EXIT);
		return (1);
	}
	if (data->cmd == NULL || data->cmd->argv == NULL)
	{
		free_exit(data, env, DONT_EXIT);
		return (1);
	}
	return (0);
}

void	prompt(t_data data)
{
	char	**env;

	data.input = readline("minishell$ ");
	if (g_sig != 0)
	{
		set_exit_status(data.env, g_sig);
		g_sig = 0;
	}
	ft_wait_input(&data);
	if (data.input == NULL)
		free_exit(&data, NULL, 1);
	if (is_empty_input(data.input) != 0)
	{
		free(data.input);
		return ;
	}
	add_history(data.input);
	env = env_to_array(data.env, EXPAND);
	cmd_init(&data);
	cmd_setup(&data, data.cmd, data.input, env);
	if (check_early_return(&data, env) != 0)
		return ;
	ft_execve(data.cmd, &data, env);
	free_exit(&data, env, DONT_EXIT);
}
