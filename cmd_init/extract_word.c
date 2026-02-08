#include "../minishell.h"

int	end_quote(const char *input, char quote)
{
	int	i;

	i = 1;
	while (input[i] != '\0' && input[i] != quote)
		i++;
	return (i);
}

static int	word_len(const char *input, int *quoted)
{
	int	end;

	end = 0;
	while (input[end] != '\0' && ft_isspace(input[end]) == 0 \
		&& is_special_char(input[end]) == 0)
	{
		if (input[end] == '\'' || input[end] == '\"')
		{
			end += end_quote(&input[end], input[end]) + 1;
			*quoted = 1;
		}
		else
			end++;
	}
	return (end);
}

int	extract_word_token(const char *input, t_token **token)
{
	int		end;
	int		quoted;

	quoted = 0;
	end = word_len(input, &quoted);
	if (end == 0)
		return (*token = NULL, 0);
	*token = malloc(sizeof(t_token));
	if (!*token)
		return (0);
	(*token)->type = WORD;
	(*token)->value = ft_substr(input, 0, end);
	(*token)->split = 0;
	(*token)->quoted = quoted;
	(*token)->next = NULL;
	return (end);
}
