#include "../minishell.h"

static void	heredoc_init(t_cmd *cmd)
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

t_cmd	*get_last_cmd(t_data *data)
{
	t_cmd	*temp;

	temp = data->cmd;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

int	is_special_char(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}
