#include "./minishell.h"

void	put_in_path(t_cmd *cmd, char **ev)
{
	t_cmd	*head;

	head = cmd;
	while (head != NULL)
	{
		if (head->argv != NULL && head->argv[0] != NULL)
			head->path = search_path(head->argv[0], ev);
		head = head->next;
	}
}

void	cmd_setup(t_cmd *cmd, char *input, char **ev)
{
	t_token	*tokens;

	tokens = tokenize(input);
	if (tokens == NULL)
		return ;
	put_in_cmd(cmd, &tokens);
	free_tokens(tokens);
	put_in_path(cmd, ev);
}
