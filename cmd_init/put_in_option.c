#include "../minishell.h"

static void	put_in_redir_in(t_cmd *cmd, t_token **tokens)
{
	char		*infile;
	int			fd;

	if ((*tokens)->type != REDIR_IN && (*tokens)->type != HEREDOC)
		return ;
	if (cmd->type != REDIR_OUT && cmd->type != REDIR_APPEND)
		cmd->type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (*tokens == NULL || (*tokens)->type != WORD)
		return ;
	infile = (*tokens)->value;
	fd = open(infile, O_RDONLY);
	if (fd >= 0)
		close(fd);
	if (cmd->type != REDIR_OUT && cmd->type != REDIR_APPEND)
	{
		if (cmd->infile != NULL)
			free(cmd->infile);
		cmd->infile = ft_strdup(infile);
	}
	*tokens = (*tokens)->next;
}

static void	put_in_redir_out(t_cmd *cmd, t_token **tokens)
{
	char		*outfile;
	int			fd;

	if (*tokens == NULL)
		return ;
	if ((*tokens)->type != REDIR_OUT && (*tokens)->type != REDIR_APPEND)
		return ;
	cmd->type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (*tokens == NULL || (*tokens)->type != WORD)
		return ;
	outfile = (*tokens)->value;
	if (cmd->type == REDIR_OUT)
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd >= 0)
		close(fd);
	if (cmd->outfile != NULL)
		free(cmd->outfile);
	cmd->outfile = ft_strdup(outfile);
	*tokens = (*tokens)->next;
}

static void	handle_pipe(t_data *data, t_cmd **cmd, t_token **temp)
{
	cmd_init(data);
	*cmd = get_last_cmd(data);
	*temp = (*temp)->next;
}

void	put_in_cmd(t_data *data, t_cmd *cmd, t_token **tokens)
{
	t_token	*temp;
	t_cmd	*current_cmd;

	temp = *tokens;
	current_cmd = cmd;
	while (temp != NULL)
	{
		if (temp->type == WORD)
			put_in_word(current_cmd, &temp);
		else if (temp->type == REDIR_IN)
			put_in_redir_in(current_cmd, &temp);
		else if (temp->type == HEREDOC)
		{
			if (handle_heredoc(data, current_cmd, &temp) != 0)
				return ;
		}
		else if (temp->type == REDIR_OUT || temp->type == REDIR_APPEND)
			put_in_redir_out(current_cmd, &temp);
		else if (temp->type == PIPE)
			handle_pipe(data, &current_cmd, &temp);
		else
			temp = temp->next;
	}
}
