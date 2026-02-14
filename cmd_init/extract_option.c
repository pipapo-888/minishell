/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_option.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:53:59 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 13:54:00 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	extract_pipe_token(t_token **token)
{
	*token = malloc(sizeof(t_token));
	if (!*token)
		return (0);
	(*token)->type = PIPE;
	(*token)->value = ft_strdup("|");
	(*token)->split = 0;
	(*token)->quoted = 0;
	(*token)->next = NULL;
	return (1);
}

int	extract_heredoc(t_token **token)
{
	*token = malloc(sizeof(t_token));
	if (!*token)
		return (0);
	(*token)->type = HEREDOC;
	(*token)->value = ft_strdup("<<");
	(*token)->split = 0;
	(*token)->quoted = 0;
	(*token)->next = NULL;
	return (2);
}

int	extract_redirect_in(t_token **token)
{
	*token = malloc(sizeof(t_token));
	if (!*token)
		return (0);
	(*token)->type = REDIR_IN;
	(*token)->value = ft_strdup("<");
	(*token)->split = 0;
	(*token)->quoted = 0;
	(*token)->next = NULL;
	return (1);
}

int	extract_redirect_out(const char *input, t_token **token)
{
	*token = malloc(sizeof(t_token));
	if (!*token)
		return (0);
	(*token)->split = 0;
	(*token)->quoted = 0;
	(*token)->next = NULL;
	if (input[0] == '>')
	{
		if (input[1] == '>')
		{
			(*token)->type = REDIR_APPEND;
			(*token)->value = ft_strdup(">>");
			return (2);
		}
		else
		{
			(*token)->type = REDIR_OUT;
			(*token)->value = ft_strdup(">");
			return (1);
		}
	}
	free(*token);
	return (*token = NULL, 0);
}
