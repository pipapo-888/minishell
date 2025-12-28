/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:16:37 by habe              #+#    #+#             */
/*   Updated: 2025/05/14 19:42:21 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	src;
	size_t			count;

	src = (unsigned char)c;
	count = 0;
	while (count < n)
	{
		((unsigned char *)s)[count] = src;
		count++;
	}
	return (s);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char buffer[10] = "abcdefghi";

// 	ft_memset(buffer + 2, 'X', 3);
// 	printf("Result: %s\n", buffer); // Result: abXXXfghi

// 	return (0);
// }
