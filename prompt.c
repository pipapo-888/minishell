#include "./minishell.h"

void	prompt(t_data data)
{
	char	**env;

	env = env_to_array(data.env);
	data.cmd = malloc(sizeof(t_cmd));
	if (data.cmd == NULL)
		return ;
	data.cmd->argv = NULL;
	data.cmd->path = NULL;
	data.cmd->infile = NULL;
	data.cmd->outfile = NULL;
	data.cmd->type = NO_REDIR;
	data.cmd->next = NULL;
	data.input = readline("minishell$ ");
	if (data.input == NULL || data.input[0] == '\0')
	{
		free(data.input);
		free(data.cmd);
		if (data.input == NULL)
			exit(1);
		return ;
	}
	add_history(data.input);
	cmd_init(data.cmd, data.input, env);
	if (data.cmd->argv == NULL)
	{
		free(data.input);
		free(data.cmd);
		return ;
	}
	ft_execve(data.cmd, &data, env);
	free_split(data.cmd->argv);
	free(data.cmd->path);
	free(data.cmd);
	free(data.input);
}
