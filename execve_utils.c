/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:18:55 by habe              #+#    #+#             */
/*   Updated: 2026/02/14 15:19:45 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	set_status_child_process(t_data *data, int status)
{
	if (WIFEXITED(status))
		set_exit_status(data->env, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		set_exit_status(data->env, 128 + WTERMSIG(status));
	}
}

void	check_access_deny(t_data *data, char **env)
{
	struct stat	st;

	if (stat(data->cmd->path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmd->argv[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	else if (access(data->cmd->path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmd->argv[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else
		return ;
	free_exit(data, env, ACCESS_DENY);
}

void	check_no_command(t_data *data, char *argv, char **env)
{
	if (ft_strchr(argv, '/') != NULL || get_env_value(env, "PATH") == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	free_exit(data, env, NO_COMMAND);
}
