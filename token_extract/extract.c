#include "../minishell.h"

int	extract_quoted_token(const char *input, t_token **token)
{
	int		end_quote;
	char	c;

	end_quote = 1;
	c = input[0];
	while (input[end_quote] != '\0' && input[end_quote] != c)
		end_quote++;
	if (input[end_quote] != c)
		return (*token = NULL, 0);
	*token = malloc(sizeof(t_token));
	if (!*token)
		return (0);
	(*token)->type = WORD;
	(*token)->value = ft_substr(input, 1, end_quote - 1);
	(*token)->next = NULL;
	return (end_quote + 1);
}

int	extract_pipe_token(const char *input, t_token **token)
{
	if (input[0] != '|')
		return (*token = NULL, 0);
	*token = malloc(sizeof(t_token));
	if (!*token)
		return (0);
	(*token)->type = PIPE;
	(*token)->value = ft_substr(input, 0, 1);
	(*token)->next = NULL;
	return (1);
}

int	extract_redirect_token(const char *input, t_token **token)
{
	*token = malloc(sizeof(t_token));
	if (!*token)
		return (0);
	(*token)->next = NULL;
	if (input[0] == '<')
	{
		if (input[1] == '<')
		{
			(*token)->type = HEREDOC;
			(*token)->value = ft_substr(input, 0, 2);
			return (2);
		}
		else
		{
			(*token)->type = REDIR_IN;
			(*token)->value = ft_substr(input, 0, 1);
			return (1);
		}
	}
	else if (input[0] == '>')
	{
		if (input[1] == '>')
		{
			(*token)->type = REDIR_APPEND;
			(*token)->value = ft_substr(input, 0, 2);
			return (2);
		}
		else
		{
			(*token)->type = REDIR_OUT;
			(*token)->value = ft_substr(input, 0, 1);
			return (1);
		}
	}
	free(*token);
	return (*token = NULL, 0);
}

int	extract_word_token(const char *input, t_token **token)
{
	int		end;

	end = 0;
	while (input[end] != '\0' && ft_isspace(input[end]) == 0
		&& input[end] != '|' && input[end] != '<' && input[end] != '>')
		end++;
	if (end == 0)
		return (*token = NULL, 0);
	*token = malloc(sizeof(t_token));
	if (!*token)
		return (0);
	(*token)->type = WORD;
	(*token)->value = ft_substr(input, 0, end);
	(*token)->next = NULL;
	return (end);
}
