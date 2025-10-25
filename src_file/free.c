/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:00:15 by babe              #+#    #+#             */
/*   Updated: 2025/09/24 12:02:10 by babe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_split(char **sp)
{
	int	i;

	if (sp == NULL)
		return ;
	i = 0;
	while (sp[i] != NULL)
	{
		free(sp[i]);
		i++;
	}
	free(sp);
}

static void	free_single(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->argv != NULL)
	{
		free_split(cmd->argv);
		cmd->argv = NULL;
	}
	if (cmd->path != NULL)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
}

void	free_cmd(t_cmd *c1, t_cmd *c2)
{
	free_single(c1);
	free_single(c2);
}

void	free_all(t_px *px)
{
	if (px == NULL)
		return ;
	free_cmd(px->c1, px->c2);
	if (px->c1 != NULL)
	{
		free(px->c1);
		px->c1 = NULL;
	}
	if (px->c2 != NULL)
	{
		free(px->c2);
		px->c2 = NULL;
	}
}
