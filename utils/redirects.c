/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:55:30 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 13:55:31 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		write(2, "minishell: ", 12);
		perror("dup2");
	}
	close(pipefd[0]);
}

int	setup_redirects(t_cmd *cmd)
{
	int	fd;

	if (cmd == NULL)
		return (1);
	if (cmd->heredoc->content != NULL)
		heredoc(cmd);
	else if (cmd->infile != NULL)
	{
		fd = open_infile(cmd->infile);
		if (fd < 0)
			return (1);
		if (dup2_and_close(fd, STDIN_FILENO) < 0)
			return (1);
	}
	if (cmd->outfile != NULL)
	{
		fd = open_outfile(cmd->outfile, cmd->type);
		if (fd < 0)
			return (1);
		if (dup2_and_close(fd, STDOUT_FILENO) < 0)
			return (1);
	}
	return (0);
}

int	save_and_redirects(t_cmd *cmd, int *saved_stdout)
{
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout < 0)
	{
		write(2, "minishell: ", 12);
		perror("dup");
		return (-1);
	}
	return (setup_redirects(cmd));
}
