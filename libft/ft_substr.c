/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <@student.42tokyo.jp>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:38:20 by habe              #+#    #+#             */
/*   Updated: 2025/05/15 15:13:37 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	copy_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
	{
		sub = malloc(1);
		if (sub == NULL)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	copy_len = ft_strlen(s + start);
	if (copy_len > len)
		copy_len = len;
	sub = malloc(copy_len + 1);
	if (sub == NULL)
		return (NULL);
	ft_strlcpy(sub, s + start, copy_len + 1);
	return (sub);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	char *sub;

// 	sub = ft_substr("Hello, world!", 7, 5);
// 	if (sub)
// 	{
// 		printf("Result: \"%s\"\n", sub); 
// 		free(sub);
// 	}

// 	sub = ft_substr("libft", 0, 3);
// 	if (sub)
// 	{
// 		printf("Result: \"%s\"\n", sub);
// 		free(sub);
// 	}

// 	sub = ft_substr("libft", 10, 5);
// 	if (sub)
// 	{
// 		printf("Result: \"%s\"\n", sub);
// 		free(sub);
// 	}

// 	return (0);
// }
