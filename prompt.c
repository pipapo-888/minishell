#include "./minishell.h"

void	prompt(char **ev, t_data data)
{
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
	cmd_init(data.cmd, data.input, ev);
	if (data.cmd->argv == NULL)
	{
		free(data.input);
		free(data.cmd);
		return ;
	}
	ft_execve(data.cmd, &data, ev);
	free_split(data.cmd->argv);
	free(data.cmd->path);
	free(data.cmd);
	free(data.input);
}
