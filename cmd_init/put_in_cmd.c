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

void	heredoc_init(t_cmd *cmd)
{
	cmd->heredoc = malloc(sizeof(t_heredoc));
	if (cmd->heredoc == NULL)
		return ;
	cmd->heredoc->content = NULL;
}

void	cmd_init(t_data *data)
{
	t_cmd	*new;
	t_cmd	*temp;

	new = malloc(sizeof(t_cmd));
	heredoc_init(new);
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

void	ft_heredoc(t_cmd *cmd, char *key, int quoted, t_env *env)
{
	char	*line;
	char	*content;
	char	*tmp;

	cmd->heredoc->content = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			line = ft_strdup("");
		if (ft_strcmp(line, key) == 0)
		{
			free(line);
			break ;
		}
		if (quoted == 0 && ft_strchr(line, '$') != NULL)
		{
			content = expand_variables(line, env);
			free(line);
			if (content == NULL)
				content = ft_strdup("");
		}
		else
			content = line;
		tmp = ft_strjoin(content, "\n");
		cmd->heredoc->content = free_strjoin(cmd->heredoc->content, tmp);
		free(content);
		free(tmp);
	}
	cmd->type = HEREDOC;
}

static t_cmd	*get_last_cmd(t_data *data)
{
	t_cmd	*temp;

	temp = data->cmd;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
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
			temp = temp->next;
			if (temp != NULL && temp->type == WORD)
			{
				ft_heredoc(current_cmd, temp->value, temp->quoted, data->env);
				temp = temp->next;
			}
			else
			{
				write(2, "minishell: syntax error near unexpected token `newline'\n", 56);
				return ;
			}
		}
		else if (temp->type == REDIR_OUT || temp->type == REDIR_APPEND)
			put_in_redir_out(current_cmd, &temp);
		else if (temp->type == PIPE)
		{
			cmd_init(data);
			current_cmd = get_last_cmd(data);
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
}
