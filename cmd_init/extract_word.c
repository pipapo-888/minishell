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
	(*token)->quoted = 1;
	(*token)->value = ft_substr(input, 1, end_quote - 1);
	(*token)->next = NULL;
	return (end_quote + 1);
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
	(*token)->quoted = 0;
	(*token)->value = ft_substr(input, 0, end);
	(*token)->next = NULL;
	return (end);
}
