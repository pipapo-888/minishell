/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <@student.42tokyo.jp>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:18:34 by habe              #+#    #+#             */
/*   Updated: 2025/05/15 15:12:02 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

// #include <fcntl.h>
// #include <unistd.h>

// int	main(void)
// {
// 	ft_putendl_fd("Hello, 42!", 1);
// 	ft_putendl_fd("Libft", 1);

// 	return (0);
// }
