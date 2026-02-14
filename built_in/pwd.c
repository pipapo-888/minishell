/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:50:35 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 13:50:36 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define PATHNAME_SIZE 1024

void	set_pwd_exit_status(t_data *data, int error_flag)
{
	if (error_flag)
		set_exit_status(data->env, ERROR);
	else
		set_exit_status(data->env, SUCCESS);
}

void	built_in_pwd(t_data *data, t_cmd *cmd)
{
	char	path_name[PATHNAME_SIZE];
	int		saved_stdout;
	int		error_flag;

	saved_stdout = -1;
	error_flag = 0;
	ft_memset(path_name, '\0', PATHNAME_SIZE);
	if (cmd->type != NO_REDIR && save_and_redirects(cmd, &saved_stdout) != 0)
	{
		set_exit_status(data->env, ERROR);
		return ;
	}
	if (getcwd(path_name, PATHNAME_SIZE))
	{
		ft_putstr_fd(path_name, 1);
		write(1, "\n", 1);
	}
	else
	{
		perror("pwd");
		error_flag = 1;
	}
	if (saved_stdout != -1)
		dup2_and_close(saved_stdout, STDOUT_FILENO);
	set_pwd_exit_status(data, error_flag);
}
