/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <@student.42tokyo.jp>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:16:50 by habe              #+#    #+#             */
/*   Updated: 2025/05/15 15:11:47 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest > src)
	{
		i = n;
		while (i > 0)
		{
			i--;
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char str[] = "abcdef";

// 	ft_memmove(str, str + 2, 4);
// 	str[4] = '\0';
// 	printf("Result: %s\n", str); // Result: cdef

// 	char str2[] = "abcdef";

// 	ft_memmove(str2 + 2, str2, 4);
// 	str2[6] = '\0';
// 	printf("Result: %s\n", str2); // Result: ababcd

// 	return (0);
// }
