/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:44:24 by habe              #+#    #+#             */
/*   Updated: 2026/02/17 19:31:30 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*handle_single_quote(char *result, char *str, int *i)
{
	(*i)++;
	while (str[*i] != '\0' && str[*i] != '\'')
	{
		result = append_char(result, str[*i]);
		(*i)++;
	}
	return (result);
}

static char	*handle_double_quote(char *result, char *str, int *i, t_env *env)
{
	(*i)++;
	while (str[*i] != '\0' && str[*i] != '"')
	{
		if (str[*i] == '$')
			result = append_expanded(result, str, i, env);
		else
			result = append_char(result, str[*i]);
		(*i)++;
	}
	return (result);
}

char	*expand_single_token(t_token *token, t_env *env)
{
	char	*result;
	int		i;

	if (!token->value)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	token->split = 0;
	while (token->value[i] != '\0')
	{
		if (token->value[i] == '\'')
			result = handle_single_quote(result, token->value, &i);
		else if (token->value[i] == '"')
			result = handle_double_quote(result, token->value, &i, env);
		else if (token->value[i] == '$')
		{
			token->split = 1;
			result = append_expanded(result, token->value, &i, env);
		}
		else
			result = append_char(result, token->value[i]);
		i++;
	}
	return (result);
}
