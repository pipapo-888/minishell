/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:28:43 by habe              #+#    #+#             */
/*   Updated: 2025/09/28 09:52:22 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	has_slash(const char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	bad_command(t_cmd *c)
{
	if (c == NULL)
		return (1);
	if (c->path == NULL)
		return (1);
	if (c->argv == NULL)
		return (1);
	if (c->argv[0] == NULL)
		return (1);
	if (c->argv[0][0] == '\0')
		return (1);
	return (0);
}

void	close_safe(int *fd)
{
	if (fd != NULL && *fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

void	close_and_perror(int pfd[2], const char *msg)
{
	close_safe(&pfd[0]);
	close_safe(&pfd[1]);
	if (msg != NULL)
		perror_print(msg);
}
