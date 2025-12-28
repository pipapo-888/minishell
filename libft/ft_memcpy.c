/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <@student.42tokyo.jp>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:09:49 by habe              #+#    #+#             */
/*   Updated: 2025/05/15 15:11:07 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	count;

	if (dest == NULL && src == NULL)
		return (NULL);
	count = 0;
	while (count < n)
	{
		((unsigned char *)dest)[count] = ((unsigned char *)src)[count];
		count++;
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char src[] = "Hello, world!";
// 	char dest[20];

// 	ft_memcpy(dest, src, 6);
// 	dest[6] = '\0';
// 	printf("Result: %s\n", dest); //

// 	ft_memcpy(dest + 7, "GPT", 3);
// 	dest[10] = '\0';
// 	printf("Result: %s\n", dest); //

// 	return (0);
// }
