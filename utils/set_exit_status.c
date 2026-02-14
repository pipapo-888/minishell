/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:55:38 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 13:55:39 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_exit_status(t_env *env, int status)
{
	t_env	*node;
	char	*new_value;

	node = find_key(env, "?");
	if (!node)
		return ;
	new_value = ft_itoa(status);
	if (!new_value)
		return ;
	free(node->value);
	node->value = new_value;
}
