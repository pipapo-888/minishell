/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_single.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:53:51 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 13:53:52 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_single_var(char *str, int *i, t_env *env)
{
	char	*key;
	char	*value;
	int		var_len;

	(*i)++;
	if (str[*i] == '\0' || (!is_valid_variable_char(str[*i], 1)
			&& str[*i] != '?'))
	{
		(*i)--;
		return (ft_strdup("$"));
	}
	if (str[*i] == '?')
	{
		return (get_env_var("?", env));
	}
	var_len = get_var_len(&str[*i]);
	if (var_len == 0)
		return (ft_strdup(""));
	key = ft_substr(str, *i, var_len);
	value = get_env_var(key, env);
	free(key);
	*i += var_len - 1;
	return (value);
}
