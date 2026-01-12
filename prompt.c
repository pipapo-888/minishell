#include "./minishell.h"

void	prompt(t_data data)
{
	char	**env;

	env = env_to_array(data.env);
	cmd_init(&data);
	data.input = readline("minishell$ ");
	if (data.input == NULL || data.input[0] == '\0')
	{
		free_all(&data);
		if (data.input == NULL)
			exit(1);
		return ;
	}
	add_history(data.input);
	cmd_setup(&data, data.cmd, data.input, env);
	if (data.cmd->argv == NULL)
	{
		free_all(&data);
		return ;
	}
	ft_execve(data.cmd, &data, env);
	free_all(&data);
	free_split(env);
}
