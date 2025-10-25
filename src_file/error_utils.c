/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 09:49:48 by habe              #+#    #+#             */
/*   Updated: 2025/09/28 12:23:52 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	usage_print_exit(void)
{
	write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 38);
	exit(1);
}

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
