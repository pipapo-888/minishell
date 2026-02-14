/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:55:22 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 13:55:23 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_infile(const char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
	{
		write(2, "minishell: ", 11);
		perror(infile);
		return (-1);
	}
	return (fd);
}

int	open_outfile(const char *outfile, t_token_type type)
{
	int	fd;

	if (type == REDIR_OUT)
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_APPEND)
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	if (fd < 0)
	{
		write(2, "minishell: ", 11);
		perror(outfile);
		return (-1);
	}
	return (fd);
}
