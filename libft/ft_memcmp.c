/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <@student.42tokyo.jp>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:11:23 by habe              #+#    #+#             */
/*   Updated: 2025/05/15 15:10:57 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_cpy;
	const unsigned char	*s2_cpy;
	size_t				i;

	s1_cpy = (const unsigned char *)s1;
	s2_cpy = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_cpy[i] != s2_cpy[i])
			return ((int)s1_cpy[i] - (int)s2_cpy[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char str1[] = "abcdef";
// 	char str2[] = "abcdez";
// 	char str3[] = "abcdef";

// 	printf("cmp1: %d\n", ft_memcmp(str1, str2, 6));
// 	printf("cmp2: %d\n", ft_memcmp(str1, str3, 6));
// 	printf("cmp3: %d\n", ft_memcmp(str1, str2, 4));

// 	return (0);
// }
