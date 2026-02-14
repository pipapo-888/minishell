/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:09:45 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 16:15:44 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*next;

	while (env != NULL)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
}

void	free_exit(t_data *data, char **env, int status)
{
	if (data != NULL)
		free_all(data);
	if (env != NULL)
		free_split(env);
	if (status == DONT_EXIT)
		return ;
	if (data != NULL)
		free_env_list(data->env);
	rl_clear_history();
	exit(status);
}
