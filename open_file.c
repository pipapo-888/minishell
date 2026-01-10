#include "./minishell.h"

int	open_infile(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->infile, O_RDONLY);
	if (fd < 0)
	{
		perror(cmd->infile);
		return (-1);
	}
	return (fd);
}

int	open_outfile(t_cmd *cmd)
{
	int	fd;

	if (cmd->type == REDIR_OUT)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->type == REDIR_APPEND)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	if (fd < 0)
	{
		perror(cmd->outfile);
		return (-1);
	}
	return (fd);
}
