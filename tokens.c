#include "./minishell.h"

int	skip_spaces(const char *input)
{
	int	i;

	i = 0;
	while (ft_isspace(input[i]) == 1)
		i++;
	return (i);
}

t_token	*tokenize(const char *input)
{
	t_token	*head;
	t_token	*current;
	t_token	*new_token;
	int		i;
	int		len;

	head = NULL;
	current = NULL;
	i = 0;
	while (input[i] != '\0')
	{
		i += skip_spaces(&input[i]);
		if (input[i] == '\0')
			break ;
		len = 0;
		if (input[i] == '"' || input[i] == '\'')
			new_token = extract_quoted_token(&input[i], &len);
		else if (input[i] == '|')
			new_token = extract_pipe_token(&input[i], &len);
		else if (input[i] == '<' || input[i] == '>')
			new_token = extract_redirect_token(&input[i], &len);
		else
			new_token = extract_word_token(&input[i], &len);
		if (new_token == NULL)
			break ;
		if (head == NULL)
			head = new_token;
		else
			current->next = new_token;
		current = new_token;
		i += len;
	}
	return (head);
}

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp != NULL)
	{
		free(temp->value);
		temp = temp->next;
	}
	free(tokens);
}