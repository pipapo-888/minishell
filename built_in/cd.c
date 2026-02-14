/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:49:57 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 13:50:00 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	argument_count(char **argv)
{
	int	count;

	count = 0;
	while (argv[count] != NULL)
		count++;
	return (count);
}

static void	update_oldpwd(t_data *data, char *old_path)
{
	t_env	*oldpwd;

	oldpwd = find_key(data->env, "OLDPWD");
	if (oldpwd)
	{
		if (oldpwd->value)
			free(oldpwd->value);
		oldpwd->value = ft_strdup(old_path);
	}
}

static int	handle_cd_path(t_data *data, t_cmd *cmd, char *path)
{
	if (!path && (cmd->argv[1] == NULL || ft_strcmp(cmd->argv[1], "~") == 0))
	{
		set_exit_status(data->env, ERROR);
		ft_putstr_fd("cd: HOME not set", 2);
		return (1);
	}
	if (!path)
	{
		set_exit_status(data->env, ERROR);
		ft_putstr_fd("cd: OLDPWD not set", 2);
		return (1);
	}
	if (chdir(path) != 0)
	{
		set_exit_status(data->env, ERROR);
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		return (1);
	}
	return (0);
}

void	built_in_cd(t_cmd *cmd, char **ev, t_data *data)
{
	char	*path;
	char	old_path[4096];

	if (argument_count(cmd->argv) > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		set_exit_status(data->env, ERROR);
		return ;
	}
	if (getcwd(old_path, sizeof(old_path)) == NULL)
		old_path[0] = '\0';
	path = cmd->argv[1];
	if (path == NULL || ft_strcmp(path, "~") == 0)
		path = get_env_value(ev, "HOME");
	else if (ft_strcmp(path, "-") == 0)
		path = get_env_value(ev, "OLDPWD");
	if (handle_cd_path(data, cmd, path) == 1)
		return ;
	set_exit_status(data->env, SUCCESS);
	if (old_path[0] != '\0')
		update_oldpwd(data, old_path);
}
