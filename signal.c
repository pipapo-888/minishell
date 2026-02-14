/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:56:05 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 13:56:06 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	(void)sig;
	g_sig = SIG_INT_FAIL;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	heredoc_handler(int sig)
{
	(void)sig;
	g_sig = SIG_INT_FAIL;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	close(STDIN_FILENO);
}
