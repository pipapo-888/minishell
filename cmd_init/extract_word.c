#include "../minishell.h"

int	end_quote(const char *input, char quote)
{
	int	i;

	i = 1;
	while (input[i] != '\0' && input[i] != quote)
		i++;
	return (i);
}

int	extract_word_token(const char *input, t_token **token)
{
	int		end;

	end = 0;
	while (input[end] != '\0' && ft_isspace(input[end]) == 0 \
		&& is_special_char(input[end]) == 0)
	{
		if (input[end] == '\'' || input[end] == '\"')
			end += end_quote(&input[end], input[end]) + 1;
		else
			end++;
	}
	if (end == 0)
		return (*token = NULL, 0);
	*token = malloc(sizeof(t_token));
	if (!*token)
		return (0);
	(*token)->type = WORD;
	(*token)->value = ft_substr(input, 0, end);
	(*token)->split = 0;
	(*token)->next = NULL;
	return (end);
}
