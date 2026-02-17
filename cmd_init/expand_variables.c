/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:53:56 by knomura           #+#    #+#             */
/*   Updated: 2026/02/17 18:45:12 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*expand_single_var(char *str, int *i, t_env *env)
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

char	*append_expanded(char *result, char *str, int *i, t_env *env)
{
	char	*temp;
	char	*expanded;

	expanded = expand_single_var(str, i, env);
	temp = result;
	result = ft_strjoin(result, expanded);
	free(temp);
	free(expanded);
	return (result);
}

char	*append_char(char *result, char c)
{
	char	*temp;

	temp = result;
	result = ft_strjoin_char(result, c);
	free(temp);
	return (result);
}

char	*expand_variables(char *str, t_env *env)
{
	char	*result;
	int		i;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			result = append_expanded(result, str, &i, env);
		else
			result = append_char(result, str[i]);
		i++;
	}
	return (result);
}
