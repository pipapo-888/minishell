#include "./minishell.h"

void	setup_redirects(t_cmd *cmd)
{
	int	fd;

	if (cmd == NULL)
		return ;
	if (cmd->infile != NULL)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
		{
			perror(cmd->infile);
			return ;
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->outfile != NULL)
	{
		if (cmd->type == REDIR_APPEND)
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(cmd->outfile);
			return ;
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
