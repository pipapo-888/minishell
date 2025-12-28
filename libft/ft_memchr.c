/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <@student.42tokyo.jp>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:42:05 by habe              #+#    #+#             */
/*   Updated: 2025/05/15 15:10:46 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s_cpy;
	size_t				i;

	s_cpy = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (s_cpy[i] == (unsigned char)c)
			return ((void *)&s_cpy[i]);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	char str[] = "Hello, world!";
// 	char *result;

// 	result = ft_memchr(str, 'w', 13);
// 	if (result)
// 		printf("Found: %s\n", result);
// 	else
// 		printf("Not found\n");

// 	result = ft_memchr(str, 'z', 13);
// 	if (result)
// 		printf("Found: %s\n", result);
// 	else
// 		printf("Not found\n");

// 	result = ft_memchr(str, ',', 5);
// 	if (result)
// 		printf("Found: %s\n", result); 
// 	else
// 		printf("Not found\n");

// 	return (0);
// }
