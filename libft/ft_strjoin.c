/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:01:17 by habe              #+#    #+#             */
/*   Updated: 2025/05/14 20:05:29 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*ans;
	unsigned int	s1_len;
	unsigned int	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ans = malloc(s1_len + s2_len + 1);
	if (ans == NULL)
		return (NULL);
	ft_strlcpy(ans, s1, s1_len + 1);
	ft_strlcat(ans, s2, s1_len + s2_len + 1);
	return (ans);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	char *result;

// 	result = ft_strjoin("Hello, ", "world!");
// 	if (result)
// 	{
// 		printf("Result: %s\n", result); // Result: Hello, world!
// 		free(result);
// 	}
// 	else
// 	{
// 		printf("ft_strjoin failed\n");
// 	}

// 	return (0);
// }
