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
	int		fd;

	fd = -1;
	if (*tokens != NULL && ((*tokens)->type == REDIR_OUT || \
				(*tokens)->type == REDIR_APPEND))
	{
		cmd->type = (*tokens)->type;
		*tokens = (*tokens)->next;
		if (*tokens != NULL && (*tokens)->type == WORD)
		{
			cmd->outfile = ft_strdup((*tokens)->value);
			fd = open_outfile(cmd);
			dup2_and_close(fd, STDOUT_FILENO);
			*tokens = (*tokens)->next;
		}
	}
}

void	cmd_init(t_cmd *cmd)
{
	cmd->argv = NULL;
	cmd->path = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->type = NO_REDIR;
	cmd->next = NULL;
}

void	put_in_cmd(t_cmd *cmd, t_token **tokens)
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
			cmd->next = malloc(sizeof(t_cmd));
			if (cmd->next == NULL)
				return ;
			cmd = cmd->next;
			cmd_init(cmd);
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
}
