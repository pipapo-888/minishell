/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <@student.42tokyo.jp>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:21:34 by habe              #+#    #+#             */
/*   Updated: 2025/05/15 15:12:18 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
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
