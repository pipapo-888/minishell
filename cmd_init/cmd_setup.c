#include "../minishell.h"

void	put_in_path(t_cmd *cmd, char **ev)
{
	t_cmd	*head;

	head = cmd;
	while (head != NULL)
	{
		if (ft_strchr(head->argv[0], '/') != NULL)
		{
			if (access(head->argv[0], X_OK) == 0)
				head->path = ft_strdup(head->argv[0]);
		}
		else if (head->argv != NULL && head->argv[0] != NULL)
			head->path = search_path(head->argv[0], ev);
		head = head->next;
	}
}

void	expand_tokens(t_token *token, t_env *env)
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

void	cmd_setup(t_data *data, t_cmd *cmd, char *input, char **ev)
{
	t_token	*tokens;

	tokens = tokenize(input);
	if (tokens == NULL)
		return ;
	expand_tokens(tokens, data->env);
	put_in_cmd(data, cmd, &tokens);
	free_tokens(tokens);
	put_in_path(cmd, ev);
}
