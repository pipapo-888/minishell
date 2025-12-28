/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 09:49:48 by habe              #+#    #+#             */
/*   Updated: 2025/12/28 16:57:02 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	cmd_not_print(t_cmd *cmd)
{
	int	i;

	i = 0;
	write(2, "pipex: ", 7);
	while (cmd->argv[i] != NULL)
	{
		write(2, cmd->argv[i], ft_strlen(cmd->argv[i]));
		write(2, " ", 1);
		i++;
	}
	write(2, ": command not found\n", 20);
}

void	perror_print(const char *msg)
{
	write(2, "pipex: ", 7);
	perror(msg);
}
