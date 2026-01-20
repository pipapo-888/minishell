/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:21:34 by habe              #+#    #+#             */
/*   Updated: 2026/01/17 12:07:39 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}

// #include <unistd.h>

// int	main(void)
// {
// 	ft_putstr_fd("Hello, world!", 1);
// 	ft_putstr_fd("\n", 1);

// 	ft_putstr_fd("Libft is fun.", 1);
// 	ft_putstr_fd("\n", 1);

// 	return (0);
// }
