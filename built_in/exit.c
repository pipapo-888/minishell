/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:50:17 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 15:04:38 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	put_numeric_error_exit(t_data *data, t_cmd *cmd, char **env)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->argv[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	set_exit_status(data->env, SHELL_ERROR);
	free_exit(data, env, SHELL_ERROR);
}

static int	is_numeric_digit(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (arg[i] == '\0')
		return (1);
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	too_many_arguments(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd->argv[count] != NULL)
		count++;
	if (count > 2)
		return (1);
	return (0);
}

void	built_in_exit(t_data *data, t_cmd *cmd, char **env)
{
	long long	argv;
	int			status;

	ft_putstr_fd("exit\n", 2);
	if (cmd->argv[1] == NULL)
		free_exit(data, env, SUCCESS);
	else if (is_numeric_digit(cmd->argv[1]) != 0
		|| llong_check(cmd->argv[1]) != 0)
		put_numeric_error_exit(data, cmd, env);
	else if (too_many_arguments(cmd) != 0)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		set_exit_status(data->env, ERROR);
		return ;
	}
	argv = ft_atoll(cmd->argv[1]);
	status = (int)(argv % 256);
	if (status < 0)
		status += 256;
	set_exit_status(data->env, status);
	free_exit(data, env, status);
}
