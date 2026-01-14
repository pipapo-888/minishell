#include "../minishell.h"

void	setup_redirects(t_cmd *cmd)
{
	int	fd;

	if (cmd == NULL)
		return ;
	if (cmd->infile != NULL)
	{
		fd = open_infile(cmd->infile);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->outfile != NULL)
	{
		fd = open_outfile(cmd->outfile, cmd->type);
		if (fd < 0)
		{
			perror(cmd->outfile);
			return ;
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
