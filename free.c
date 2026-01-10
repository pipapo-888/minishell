#include "./minishell.h"

void	free_split(char **sp)
{
	int	i;

	if (sp == NULL)
		return ;
	i = 0;
	while (sp[i] != NULL)
	{
		free(sp[i]);
		i++;
	}
	free(sp);
}

static void	free_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->argv != NULL)
		free_split(cmd->argv);
	if (cmd->path != NULL)
		free(cmd->path);
	if (cmd->infile != NULL)
		free(cmd->infile);
	if (cmd->outfile != NULL)
		free(cmd->outfile);
	free(cmd);
}

void	free_all(t_data *data)
{
	if (data == NULL)
		return ;
	if (data->cmd != NULL)
		free_cmd(data->cmd);
	if (data->input != NULL)
		free(data->input);
	data->cmd = NULL;
	data->input = NULL;
}
