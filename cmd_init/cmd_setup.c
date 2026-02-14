/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:53:41 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 14:27:01 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	put_in_path(t_cmd *cmd, char **ev)
{
	t_cmd	*head;

	head = cmd;
	while (head != NULL)
	{
		if (head->argv != NULL && ft_strchr(head->argv[0], '/') != NULL)
		{
			if (access(head->argv[0], X_OK) == 0)
				head->path = ft_strdup(head->argv[0]);
		}
		else if (head->argv != NULL && head->argv[0] != NULL)
			head->path = search_path(head->argv[0], ev);
		head = head->next;
	}
}

static void	expand_tokens(t_token *token, t_env *env)
{
	char	*temp_value;

	while (1)
	{
		temp_value = token->value;
		if (temp_value && (temp_value[0] == '"' || temp_value[0] == '\''))
			token->split = 1;
		else
			token->split = 0;
		token->value = expand_variables(token->value, env);
		free(temp_value);
		if (token->next == NULL)
			break ;
		token = token->next;
	}
}

static void	syntax_error(char *token)
{
	write(2, "minishell: ", 11);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
}

static int	is_syntax_error(t_token *tokens)
{
	if (tokens == NULL)
		return (0);
	if (tokens->type == PIPE)
	{
		syntax_error("|");
		return (1);
	}
	while (tokens != NULL)
	{
		if (is_tokens_type(tokens->type) && \
			(tokens->next == NULL || tokens->next->type != WORD))
		{
			syntax_error("newline");
			return (1);
		}
		if (tokens->type == PIPE && \
			(tokens->next == NULL || tokens->next->type == PIPE))
		{
			syntax_error("|");
			return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

void	cmd_setup(t_data *data, t_cmd *cmd, char *input, char **ev)
{
	t_token	*tokens;

	tokens = tokenize(input);
	if (tokens == NULL)
		return ;
	if (is_syntax_error(tokens) != 0)
	{
		free_tokens(tokens);
		free_all(data);
		set_exit_status(data->env, SHELL_ERROR);
		return ;
	}
	expand_tokens(tokens, data->env);
	put_in_cmd(data, cmd, &tokens);
	free_tokens(tokens);
	put_in_path(cmd, ev);
}
