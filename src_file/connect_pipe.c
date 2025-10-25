/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:18:49 by babe              #+#    #+#             */
/*   Updated: 2025/09/28 11:25:56 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	child_in_assist(t_px *px)
{
	if (px->fd_in < 0)
	{
		free_all(px);
		exit(1);
	}
	if (dup2(px->fd_in, STDIN_FILENO) < 0)
	{
		write(2, "pipex: ", 7);
		perror("dup2");
		free_all(px);
		exit(1);
	}
}

static void	child_exec_in(t_px *px, int pfd[2], char *const envp[])
{
	child_in_assist(px);
	close_safe(&px->fd_in);
	if (dup2(pfd[1], STDOUT_FILENO) < 0)
	{
		write(2, "pipex: ", 7);
		perror("dup2");
		free_all(px);
		exit(1);
	}
	close_and_perror(pfd, NULL);
	if (bad_command(px->c1) != 0)
	{
		free_all(px);
		exit(127);
	}
	execve(px->c1->path, px->c1->argv, envp);
	write(2, "pipex: ", 7);
	perror(px->c1->argv[0]);
	free_all(px);
	exit(126);
}

static void	child_out_assist(t_px *px, int pfd[2])
{
	if (dup2(pfd[0], STDIN_FILENO) < 0)
	{
		write(2, "pipex: ", 7);
		perror("dup2");
		free_all(px);
		exit(1);
	}
	if (px->fd_out < 0)
	{
		free_all(px);
		exit(1);
	}
	if (dup2(px->fd_out, STDOUT_FILENO) < 0)
	{
		write(2, "pipex: ", 7);
		perror("dup2");
		free_all(px);
		exit(1);
	}
}

static void	child_exec_out(t_px *px, int pfd[2], char *const envp[])
{
	child_out_assist(px, pfd);
	close_safe(&px->fd_out);
	close_and_perror(pfd, NULL);
	if (bad_command(px->c2) != 0)
	{
		free_all(px);
		exit(127);
	}
	execve(px->c2->path, px->c2->argv, envp);
	write(2, "pipex: ", 7);
	perror(px->c2->argv[0]);
	free_all(px);
	exit(126);
}

int	connect_pipe(t_px *px, char *const envp[])
{
	int		pfd[2];
	pid_t	p1;
	pid_t	p2;
	int		st1;
	int		st2;

	if (pipe(pfd) < 0)
		return (perror("pipe"), 1);
	p1 = fork();
	if (p1 < 0)
		return (close_and_perror(pfd, "fork"), 1);
	if (p1 == 0)
		child_exec_in(px, pfd, envp);
	p2 = fork();
	if (p2 < 0)
		return (close_and_perror(pfd, "fork"), 1);
	if (p2 == 0)
		child_exec_out(px, pfd, envp);
	close_and_perror(pfd, NULL);
	waitpid(p1, &st1, 0);
	waitpid(p2, &st2, 0);
	if (st2 == 0)
		return (0);
	return (1);
}
