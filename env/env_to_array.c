/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:54:30 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 13:54:31 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*env_entry_to_str(t_env *env)
{
	char	*tmp;
	char	*result;

	if (env->value)
	{
		tmp = ft_strjoin(env->key, "=");
		result = ft_strjoin(tmp, env->value);
		free(tmp);
		return (result);
	}
	return (ft_strdup(env->key));
}

char	**env_to_array(t_env *env, t_export_type NUM)
{
	char	**arr;
	int		size;
	int		i;

	size = env_list_size(env);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->type > NUM || env->value == NULL)
		{
			env = env->next;
			continue ;
		}
		arr[i] = env_entry_to_str(env);
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}
