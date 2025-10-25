/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:59:45 by babe              #+#    #+#             */
/*   Updated: 2025/09/28 11:59:43 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	close_files(t_px *px)
{
	close_safe(&px->fd_in);
	close_safe(&px->fd_out);
}

static int	cmd_all_set(t_px *px, char **cmd, char *const envp[])
{
	if (cmd_init(px->c1, cmd[0], envp) != 0)
	{
		free_all(px);
		return (1);
	}
	else
		px->c1->flag = 0;
	if (cmd_init(px->c2, cmd[1], envp) != 0)
	{
		free_all(px);
		return (1);
	}
	else
		px->c1->flag = 0;
	return (0);
}

static int	px_init(t_px *px, char **argv)
{
	px->c1 = malloc(sizeof(t_cmd));
	if (px->c1 == NULL)
		return (1);
	px->c2 = malloc(sizeof(t_cmd));
	if (px->c1 == NULL )
	{
		free(px->c1);
		return (1);
	}
	ft_memset(px->c1, 0, sizeof(t_cmd));
	ft_memset(px->c2, 0, sizeof(t_cmd));
	px->infile = argv[1];
	px->outfile = argv[4];
	px->fd_in = -1;
	px->fd_out = -1;
	px->end_st = 0;
	px->flag = 0;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_px	px;

	if (argc != 5)
		usage_print_exit();
	if (px_init(&px, argv) != 0)
		return (1);
	open_infile(&px, argv[1]);
	px.end_st = open_outfile(&px, argv[4]);
	if (cmd_all_set(&px, &argv[2], envp) != 0)
		return (1);
	if (px.end_st == 0)
		px.end_st = connect_pipe(&px, envp);
	else
		connect_pipe(&px, envp);
	if (px.c2->flag == 0 && px.c2->path == NULL && px.fd_out != -1)
		px.end_st = 127;
	else if (px.c2->flag == 1 && px.end_st == 1 && px.fd_out != -1)
		px.end_st = 126;
	close_files(&px);
	free_all(&px);
	return (px.end_st);
}
