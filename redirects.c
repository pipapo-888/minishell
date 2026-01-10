#include "./minishell.h"

static int	open_infile(t_cmd *cmd)
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

static int	open_outfile(t_cmd *cmd)
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

void	setup_redirects(t_cmd *cmd)
{
	int	fd;

	if (cmd == NULL)
		return ;
	if (cmd->infile != NULL)
	{
		fd = open_infile(cmd);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->outfile != NULL)
	{
		fd = open_outfile(cmd);
		if (fd < 0)
		{
			perror(cmd->outfile);
			return ;
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
