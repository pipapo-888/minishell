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

static int	handle_redirects(char *argv)
{
	if (ft_strcmp(argv, "<") == 0)
		return (0);
	else if (ft_strcmp(argv, ">") == 0)
		return (0);
	else if (ft_strcmp(argv, ">>") == 0)
		return (0);
	return (1);
}

static void	redirect_input(t_cmd *cmd, char *filename)
{
	if (cmd->infile != NULL)
		free(cmd->infile);
	cmd->infile = ft_strdup(filename);
	cmd->type = REDIR_IN;
}


void	parse_redirects(t_cmd *cmd, char **argv)
{
	int	i;

	if (cmd == NULL || argv == NULL)
		return ;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	i = 0;
	while (argv[i] != NULL)
	{
		if (handle_redirects(argv[i]) == 0)
		{
			if (argv[i + 1] == NULL)
				return ;
			redirect_input(cmd, argv[i + 1]);
			i += 2;
		}
		else
			i++;
	}
}
