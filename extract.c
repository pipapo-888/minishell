#include "./minishell.h"

t_token	*extract_quoted_token(const char *input, int *len)
{
	t_token	*token;
	int		end_quote;
	char	c;

	end_quote = 1;
	c = input[0];
	while (input[end_quote] != '\0' && input[end_quote] != c)
		end_quote++;
	if (input[end_quote] != c)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = WORD;
	token->value = ft_substr(input, 1, end_quote - 1);
	token->next = NULL;
	*len = end_quote + 1;
	return (token);
}

t_token	*extract_pipe_token(const char *input, int *len)
{
	t_token	*token;

	if (input[0] != '|')
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = PIPE;
	token->value = ft_substr(input, 0, 1);
	token->next = NULL;
	*len = 1;
	return (token);
}

t_token	*extract_redirect_token(const char *input, int *len)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	if (input[0] == '<')
	{
		if (input[1] == '<')
		{
			token->type = HEREDOC;
			token->value = ft_substr(input, 0, 2);
			*len = 2;
		}
		else
		{
			token->type = REDIR_IN;
			token->value = ft_substr(input, 0, 1);
			*len = 1;
		}
	}
	else if (input[0] == '>')
	{
		if (input[1] == '>')
		{
			token->type = REDIR_APPEND;
			token->value = ft_substr(input, 0, 2);
			*len = 2;
		}
		else
		{
			token->type = REDIR_OUT;
			token->value = ft_substr(input, 0, 1);
			*len = 1;
		}
	}
	else
	{
		free(token);
		return (NULL);
	}
	return (token);
}

t_token	*extract_word_token(const char *input, int *len)
{
	t_token	*token;
	int		end;

	end = 0;
	while (input[end] != '\0' && ft_isspace(input[end]) == 0
		&& input[end] != '|' && input[end] != '<' && input[end] != '>')
		end++;
	if (end == 0)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = WORD;
	token->value = ft_substr(input, 0, end);
	token->next = NULL;
	*len = end;
	return (token);
}