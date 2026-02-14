/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:50:13 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 13:50:14 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	built_in_env(t_data *data, t_cmd *cmd)
{
	char	**arr;
	int		i;
	int		saved_stdout;

	saved_stdout = -1;
	if (cmd->type != NO_REDIR && save_and_redirects(cmd, &saved_stdout) != 0)
	{
		set_exit_status(data->env, ERROR);
		return ;
	}
	set_exit_status(data->env, SUCCESS);
	arr = env_to_array(data->env, SHOW);
	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
	{
		ft_putstr_fd(arr[i], 1);
		write(1, "\n", 1);
		i++;
	}
	free_split(arr);
	if (saved_stdout != -1)
		dup2_and_close(saved_stdout, STDOUT_FILENO);
}
