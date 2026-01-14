#include "../minishell.h"

void	setup_redirects(t_cmd *cmd)
{
	int	fd;
	int	pipefd[2];

	if (cmd == NULL)
		return ;
	if (cmd->heredoc_content != NULL)
	{
		pipe(pipefd);
		write(pipefd[1], cmd->heredoc_content, ft_strlen(cmd->heredoc_content));
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	else if (cmd->infile != NULL)
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
