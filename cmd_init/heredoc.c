#include "../minishell.h"

static char	*expand_line(char *line, int quoted, t_env *env)
{
	char	*content;

	if (quoted || !ft_strchr(line, '$'))
		return (line);
	content = expand_variables(line, env);
	free(line);
	if (content == NULL)
		return (ft_strdup(""));
	return (content);
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
		content = expand_line(line, quoted, env);
		tmp = ft_strjoin(content, "\n");
		cmd->heredoc->content = free_strjoin(cmd->heredoc->content, tmp);
		free(content);
		free(tmp);
	}
	cmd->type = HEREDOC;
}

int	handle_heredoc(t_data *data, t_cmd *cmd, t_token **temp)
{
	*temp = (*temp)->next;
	if (*temp != NULL && (*temp)->type == WORD)
	{
		ft_heredoc(cmd, (*temp)->value, (*temp)->quoted, data->env);
		*temp = (*temp)->next;
		return (0);
	}
	write(2, "minishell: syntax error near unexpected token `newline'\n", 56);
	return (1);
}
