/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:08:50 by habe              #+#    #+#             */
/*   Updated: 2025/05/14 20:15:10 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("cmp1: %d\n", ft_strncmp("abcde", "abcde", 5));
// 	printf("cmp2: %d\n", ft_strncmp("abcde", "abcdf", 5));
// 	printf("cmp3: %d\n", ft_strncmp("abcdef", "abc", 3));
// 	printf("cmp4: %d\n", ft_strncmp("abc", "abcdef", 6));

// 	return (0);
// }
