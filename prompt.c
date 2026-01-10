#include "./minishell.h"

void	cmd_init(t_cmd *cmd)
{
	cmd->argv = NULL;
	cmd->path = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->type = NO_REDIR;
	cmd->next = NULL;
}

void	prompt(char **ev, t_data data)
{
	data.cmd = malloc(sizeof(t_cmd));
	if (data.cmd == NULL)
		return ;
	cmd_init(data.cmd);
	data.input = readline("minishell$ ");
	if (data.input == NULL || data.input[0] == '\0')
	{
		free_all(&data);
		if (data.input == NULL)
			exit(1);
		return ;
	}
	add_history(data.input);
	cmd_setup(data.cmd, data.input, ev);
	if (data.cmd->argv == NULL)
	{
		free_all(&data);
		return ;
	}
	ft_execve(data.cmd, &data, ev);
	free_all(&data);
}
