/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:55:50 by knomura           #+#    #+#             */
/*   Updated: 2026/02/21 14:33:55 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	built_in_check(t_cmd *cmd, t_data *data, char **env)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (built_in_echo(data, cmd), 0);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (built_in_cd(cmd, env, data), 0);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (built_in_pwd(data, cmd), 0);
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (built_in_export(data, cmd->argv), 0);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (built_in_unset(data, cmd->argv), 0);
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (built_in_env(data, cmd), 0);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (built_in_exit(data, cmd, env), 0);
	return (1);
}

void	child_prosess(t_data *data, char **env, int pfd[2], int prev_fd)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (prev_fd != -1)
	{
		if (dup2_and_close(prev_fd, STDIN_FILENO) < 0)
			free_exit(data, env, ERROR);
	}
	if (data->cmd->next != NULL)
	{
		close(pfd[0]);
		if (dup2_and_close(pfd[1], STDOUT_FILENO) < 0)
			free_exit(data, env, ERROR);
	}
	if (setup_redirects(data->cmd) != 0)
		free_exit(data, env, ERROR);
	if (built_in_check(data->cmd, data, env) == 0)
		free_exit(data, env, ft_atoi(get_env_var("?", data->env)));
	if (data->cmd->path == NULL)
		check_no_command(data, data->cmd->argv[0], env);
	check_access_deny(data, env);
	execve(data->cmd->path, data->cmd->argv, env);
	perror("minishell: execve:");
	free_exit(data, env, ERROR);
}

static int	update_prev_fd(int pfd[2], int prev_fd, t_cmd *cmd)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->next != NULL)
	{
		close(pfd[1]);
		return (pfd[0]);
	}
	return (-1);
}

static pid_t	handle_process(t_data *data, t_cmd *cmd, char **env)
{
	int		pfd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	while (cmd != NULL)
	{
		data->cmd = cmd;
		if (cmd->next != NULL)
			pipe(pfd);
		pid = fork();
		if (pid == 0)
			child_prosess(data, env, pfd, prev_fd);
		prev_fd = update_prev_fd(pfd, prev_fd, cmd);
		cmd = cmd->next;
	}
	return (pid);
}

void	ft_execve(t_cmd *cmd, t_data *data, char **env)
{
	int		status;
	int		last_status;
	pid_t	last_pid;
	pid_t	wpid;
	t_cmd	*head;

	head = cmd;
	if (cmd->next == NULL && built_in_check(cmd, data, env) == 0)
		return ;
	signal(SIGINT, SIG_IGN);
	last_pid = handle_process(data, cmd, env);
	data->cmd = head;
	last_status = 0;
	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == last_pid)
			last_status = status;
		wpid = wait(&status);
	}
	set_status_child_process(data, last_status);
	signal(SIGINT, handler);
}
