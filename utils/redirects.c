#include "../minishell.h"

static void	heredoc(t_cmd *cmd)
{
	int		pipefd[2];
	char	**split;
	int		i;

	split = ft_split(cmd->heredoc->content, '\n');
	if (split == NULL)
		return ;
	i = 0;
	pipe(pipefd);
	while (split[i] != NULL)
	{
		ft_putstr_fd(split[i], pipefd[1]);
		write(pipefd[1], "\n", 1);
		i++;
	}
	free_split(split);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

void	setup_redirects(t_cmd *cmd)
{
	int	fd;

	if (cmd == NULL)
		return ;
	if (cmd->heredoc->content != NULL)
		heredoc(cmd);
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
