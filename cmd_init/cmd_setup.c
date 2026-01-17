#include "../minishell.h"

void	put_in_path(t_cmd *cmd, char **ev)
{
	t_cmd	*head;

	head = cmd;
	while (head != NULL)
	{
		if (ft_has_slash(head->argv[0]) != 0)
		{
			if (access(head->argv[0], X_OK) == 0)
				head->path = ft_strdup(head->argv[0]);
			return ;
		}
		else if (head->argv != NULL && head->argv[0] != NULL)
			head->path = search_path(head->argv[0], ev);
		head = head->next;
	}
}

void	cmd_setup(t_data *data, t_cmd *cmd, char *input, char **ev)
{
	t_token	*tokens;

	tokens = tokenize(input);
	if (tokens == NULL)
		return ;
	put_in_cmd(data, cmd, &tokens);
	free_tokens(tokens);
	put_in_path(cmd, ev);
}
