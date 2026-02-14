/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:55:14 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 13:55:15 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dup2_and_close(int fd, int flag)
{
	if (dup2(fd, flag) == -1)
	{
		write(2, "minishell: ", 12);
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
