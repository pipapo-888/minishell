/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:54:26 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 14:36:18 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define DEF_PATH "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/bin"

static t_env	*create_env_node(char *envp_line)
{
	t_env	*node;
	char	*equal_pos;
	int		key_len;

	if (envp_line[0] == '?' && envp_line[1] == '=')
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equal_pos = ft_strchr(envp_line, '=');
	if (equal_pos)
	{
		key_len = equal_pos - envp_line;
		node->key = ft_substr(envp_line, 0, key_len);
		node->value = ft_strdup(equal_pos + 1);
		node->type = SHOW;
	}
	else
	{
		node->key = ft_strdup(envp_line);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}

static t_env	*create_exit_status_node(void)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup("?");
	node->value = ft_strdup("0");
	node->type = EXPAND;
	node->next = NULL;
	return (node);
}

static void	self_init_env(t_env **env)
{
	char	cwd[1024];
	char	*pwd_str;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		pwd_str = ft_strjoin("PWD=", cwd);
		env_add_back(env, create_env_node(pwd_str));
		free(pwd_str);
	}
	env_add_back(env, create_env_node("SHLVL=1"));
	env_add_back(env, create_env_node(DEF_PATH));
	env_add_back(env, create_env_node("_=/usr/bin/env"));
	env_add_back(env, create_env_node("OLDPWD"));
}

void	env_init(t_data *data, char **envp)
{
	t_env	*new_node;
	int		i;

	i = 0;
	data->env = NULL;
	while (envp[i])
	{
		new_node = create_env_node(envp[i]);
		if (new_node)
			env_add_back(&data->env, new_node);
		i++;
	}
	if (env_list_size(data->env) == 0)
		self_init_env(&data->env);
	env_add_back(&data->env, create_exit_status_node());
}
