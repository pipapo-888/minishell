/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <@student.42tokyo.jp>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:20:18 by habe              #+#    #+#             */
/*   Updated: 2025/05/15 15:12:10 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;

	nbr = (long)n;
	if (n < 0)
	{
		write(fd, "-", 1);
		nbr = -nbr;
	}
	if (nbr >= 10)
		ft_putnbr_fd(nbr / 10, fd);
	nbr = nbr % 10 + '0';
	write(fd, &nbr, 1);
}

// #include <fcntl.h>
// #include <unistd.h>

// int	main(void)
// {
// 	ft_putnbr_fd(12345, 1);
// 	ft_putchar_fd('\n', 1);

// 	ft_putnbr_fd(-9876, 1);
// 	ft_putchar_fd('\n', 1);

// 	ft_putnbr_fd(0, 1); 
// 	ft_putchar_fd('\n', 1);

// 	return (0);
// }
