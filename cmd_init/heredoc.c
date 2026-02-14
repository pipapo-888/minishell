/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:54:08 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 13:54:09 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_heredoc(t_cmd *cmd, char *key, int quoted, t_env *env)
{
	char	*line;
	char	*content;
	char	*tmp;
	int		stdin_copy;

	stdin_copy = dup(STDIN_FILENO);
	g_sig = 0;
	signal(SIGINT, heredoc_handler);
	cmd->heredoc->content = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (line == NULL || g_sig == SIG_INT_FAIL)
		{
			free(line);
			break ;
		}
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
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
	signal(SIGINT, handler);
	if (g_sig == SIG_INT_FAIL)
	{
		free(cmd->heredoc->content);
		cmd->heredoc->content = NULL;
		return (1);
	}
	cmd->type = HEREDOC;
	return (0);
}

int	handle_heredoc(t_data *data, t_cmd *cmd, t_token **temp)
{
	*temp = (*temp)->next;
	if (*temp != NULL && (*temp)->type == WORD)
	{
		if (ft_heredoc(cmd, (*temp)->value, (*temp)->quoted, data->env) != 0)
			return (1);
		*temp = (*temp)->next;
		return (0);
	}
	write(2, "minishell: syntax error near unexpected token `newline'\n", 56);
	return (1);
}
