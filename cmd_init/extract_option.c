#include "../minishell.h"

int	extract_pipe_token(t_token **token)
{
	*token = malloc(sizeof(t_token));
	if (!*token)
		return (0);
	(*token)->type = PIPE;
	(*token)->value = ft_strdup("|");
	(*token)->next = NULL;
	return (1);
}

int	extract_heredoc(t_token **token)
{
	*token = malloc(sizeof(t_token));
	if (!*token)
		return (0);
	(*token)->next = NULL;
	(*token)->type = HEREDOC;
	(*token)->value = ft_strdup("<<");
	return (2);
}

int	extract_redirect_in(t_token **token)
{
	*token = malloc(sizeof(t_token));
	if (!*token)
		return (0);
	(*token)->next = NULL;
	(*token)->type = REDIR_IN;
	(*token)->value = ft_strdup("<");
	return (1);
}

int	extract_redirect_out(const char *input, t_token **token)
{
	*token = malloc(sizeof(t_token));
	if (!*token)
		return (0);
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
