#include "./minishell.h"

static void	put_in_word(t_cmd *cmd, t_token **tokens)
{
	t_token	*counter;
	int		word_count;
	int		i;

	counter = *tokens;
	word_count = 0;
	while (counter != NULL && counter->type == WORD)
	{
		word_count++;
		counter = counter->next;
	}
	cmd->argv = malloc(sizeof(char *) * (word_count + 1));
	if (cmd->argv == NULL)
		return ;
	i = 0;
	while (*tokens != NULL && (*tokens)->type == WORD)
	{
		cmd->argv[i] = ft_strdup((*tokens)->value);
		i++;
		*tokens = (*tokens)->next;
	}
	cmd->argv[i] = NULL;
}

static void	put_in_redir_in(t_cmd *cmd, t_token **tokens)
{
	if ((*tokens)->type == REDIR_IN || (*tokens)->type == HEREDOC)
	{
		cmd->type = (*tokens)->type;
		*tokens = (*tokens)->next;
		if (*tokens != NULL && (*tokens)->type == WORD)
		{
			cmd->infile = ft_strdup((*tokens)->value);
			*tokens = (*tokens)->next;
		}
	}
}

static void	put_in_redir_out(t_cmd *cmd, t_token **tokens)
{
	int	fd;

	fd = 0;
	if (*tokens != NULL && ((*tokens)->type == REDIR_OUT
			|| (*tokens)->type == REDIR_APPEND))
	{
		cmd->type = (*tokens)->type;
		*tokens = (*tokens)->next;
		if (*tokens != NULL && (*tokens)->type == WORD)
		{
			cmd->outfile = ft_strdup((*tokens)->value);
			fd = open_outfile(cmd);
			close(fd);
			*tokens = (*tokens)->next;
		}
	}
}

void	cmd_init(t_data *data)
{
	t_cmd	*new;
	t_cmd	*temp;

	new = malloc(sizeof(t_cmd));
	if (new == NULL)
		return ;
	new->argv = NULL;
	new->path = NULL;
	new->infile = NULL;
	new->outfile = NULL;
	new->type = NO_REDIR;
	new->next = NULL;
	if (data->cmd == NULL)
		data->cmd = new;
	else
	{
		temp = data->cmd;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void	put_in_cmd(t_data *data, t_cmd *cmd, t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	while (temp != NULL)
	{
		if (temp->type == WORD)
			put_in_word(cmd, &temp);
		else if (temp->type == REDIR_IN || temp->type == HEREDOC)
			put_in_redir_in(cmd, &temp);
		else if (temp->type == REDIR_OUT || temp->type == REDIR_APPEND)
			put_in_redir_out(cmd, &temp);
		else if (temp->type == PIPE)
		{
			cmd_init(data);
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
}
