/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:14:18 by habe              #+#    #+#             */
/*   Updated: 2025/05/14 20:02:54 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ans;
	size_t	s_len;

	s_len = ft_strlen(s);
	ans = malloc(s_len + 1);
	if (ans == NULL)
		return (NULL);
	ft_strlcpy(ans, s, s_len + 1);
	return (ans);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	const char *original = "Hello, 42!";
// 	char *copy = ft_strdup(original);

// 	if (copy)
// 	{
// 		printf("Original: %s\n", original); // Original: Hello, 42!
// 		printf("Copy    : %s\n", copy);     // Copy    : Hello, 42!
// 		free(copy);
// 	}
// 	else
// 	{
// 		printf("ft_strdup failed\n");
// 	}

// 	return (0);
// }
