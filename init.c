#include "./minishell.h"

void	put_in_cmd(t_cmd *cmd, t_token *tokens)
{
	t_token	*temp;
	t_token	*counter;
	int		i;
	int		word_count;

	temp = tokens;
	word_count = 0;
	i = 0;
	while (temp != NULL)
	{
		if (temp->type == WORD)
		{
			counter = temp;

			while (counter != NULL && counter->type == WORD)
			{
				word_count++;
				counter = counter->next;
			}

			cmd->argv = malloc(sizeof(char *) * (word_count + 1));
			if (cmd->argv == NULL)
				return ;

			while (temp != NULL && temp->type == WORD)
			{
				cmd->argv[i] = ft_strdup(temp->value);
				i++;
				temp = temp->next;
			}
			cmd->argv[i] = NULL;
		}
		else if (temp->type == REDIR_IN || temp->type == HEREDOC)
		{
			cmd->type = temp->type;
			temp = temp->next;
			if (temp != NULL && temp == WORD)
				cmd->infile = ft_strdup( temp->value);
			temp = temp->next;
		}
		else if (temp->type == REDIR_OUT || temp->type == REDIR_APPEND)
		{
			cmd->type = temp->type;
			temp = temp->next;
			if (temp != NULL && temp->type == WORD)
				cmd->outfile = ft_strdup(temp->value);
			temp = temp->next;
		}
		else if (temp->type == PIPE)
		{
			cmd->next = malloc(sizeof(t_cmd));
			if (cmd->next == NULL)
				return ;
			cmd = cmd->next;
			cmd->argv = NULL;
			cmd->infile = NULL;
			cmd->outfile = NULL;
			cmd->type = NO_REDIR;
			cmd->next = NULL;
			temp = temp->next;
		}
	}
}

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
	put_in_cmd(cmd, tokens);
	free_tokens(tokens);
	put_in_path(cmd, ev);
}
