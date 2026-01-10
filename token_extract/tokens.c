#include "../minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*temp;
	t_token	*next;

	temp = tokens;
	while (temp != NULL)
	{
		next = temp->next;
		if (temp->value != NULL)
			free(temp->value);
		free(temp);
		temp = next;
	}
}

static int	skip_spaces(const char *input)
{
	int	i;

	i = 0;
	while (ft_isspace(input[i]) == 1 && input[i] != '\0')
		i++;
	return (i);
}

static int	extract_token(const char *input, t_token **token)
{
	if (input[0] == '"' || input[0] == '\'')
		return (extract_quoted_token(input, token));
	else if (input[0] == '|')
		return (extract_pipe_token(input, token));
	else if (input[0] == '<' || input[0] == '>')
		return (extract_redirect_token(input, token));
	else
		return (extract_word_token(input, token));
}

t_token	*tokenize(const char *input)
{
	t_token	*head;
	t_token	*current;
	t_token	*new_token;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (input[i] != '\0')
	{
		i += skip_spaces(&input[i]);
		if (input[i] == '\0')
			break ;
		i += extract_token(&input[i], &new_token);
		if (new_token == NULL)
			break ;
		if (head == NULL)
			head = new_token;
		else
			current->next = new_token;
		current = new_token;
	}
	return (head);
}
