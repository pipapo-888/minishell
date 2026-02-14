/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:54:39 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 13:54:40 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*create_export_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->type = SHOW;
	node->next = NULL;
	return (node);
}

void	add_new_env(t_data *data, char *key, char *value)
{
	t_env	*new_node;

	new_node = create_export_node(key, value);
	env_add_back(&data->env, new_node);
	free(key);
	if (value)
		free(value);
}

char	*get_env_var(char *key, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmp(key, env->key) == 0)
		{
			if (env->value)
				return (ft_strdup(env->value));
		}
		env = env->next;
	}
	return (ft_strdup(""));
}
