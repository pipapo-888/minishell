#include "../minishell.h"

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
	fd = open_infile(infile);
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
	fd = open_outfile(outfile, cmd->type);
	if (fd >= 0)
		close(fd);
	if (cmd->outfile != NULL)
		free(cmd->outfile);
	cmd->outfile = ft_strdup(outfile);
	*tokens = (*tokens)->next;
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
	new->heredoc_content = NULL;
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

void	ft_herdoc(t_cmd *cmd, char *key)
{
	char	*line;
	char	*content;

	content = ft_strdup("");
	if (content == NULL)
		return ;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, key) == 0)
		{
			free(line);
			break ;
		}
		content = free_strjoin(content, line);
		content = free_strjoin(content, "\n");
		free(line);
	}
	cmd->heredoc_content = content;
	cmd->type = HEREDOC;
}

void	put_in_cmd(t_data *data, t_cmd *cmd, t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	while (temp != NULL)
	{
		if (temp->type == WORD)
			put_in_word(cmd, &temp);
		else if (temp->type == REDIR_IN)
			put_in_redir_in(cmd, &temp);
		else if (temp->type == HEREDOC)
		{
			temp = temp->next;
			if (temp != NULL && temp->type == WORD)
			{
				ft_herdoc(cmd, temp->value);
				temp = temp->next;
			}
		}
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
