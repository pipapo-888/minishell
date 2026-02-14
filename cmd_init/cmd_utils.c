/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:53:46 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 13:53:47 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (new == NULL)
		return ;
	heredoc_init(new);
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
