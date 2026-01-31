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
		token->value = expand_variables(token->value, env);
		free(temp_value);
		if (token->next == NULL)
			break ;
		token = token->next;
	}
}

static int	is_tokens_type(t_token_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND || type == HEREDOC)
		return (1);
	return (0);
}

static int	is_syntax_error(t_token *tokens)
{
	if (tokens == NULL)
		return (0);
	if (tokens->type == PIPE)
	{
		write(2, "minishell: ", 11);
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	while (tokens != NULL)
	{
		if (is_tokens_type(tokens->type) && \
			(tokens->next == NULL || tokens->next->type != WORD))
		{
			write(2, "minishell: ", 11);
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
			return (1);
		}
		if (tokens->type == PIPE && \
			(tokens->next == NULL || tokens->next->type == PIPE))
		{
			write(2, "minishell: ", 11);
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
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
		data->cmd = NULL;
		set_exit_status(data->env, SHELL_ERROR);
		return ;
	}
	expand_tokens(tokens, data->env);
	put_in_cmd(data, cmd, &tokens);
	free_tokens(tokens);
	put_in_path(cmd, ev);
}
