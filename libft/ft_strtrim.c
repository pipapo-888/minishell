/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <@student.42tokyo.jp>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:06:51 by habe              #+#    #+#             */
/*   Updated: 2025/05/15 14:07:42 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (s1 == NULL)
		return (NULL);
	else if (set == NULL)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] != '\0' && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (end > 0 && ft_strchr(set, s1[end - 1]) != NULL)
		end--;
	if (start >= end)
		return (ft_strdup(""));
	return (ft_substr(s1, start, end - start));
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	char *trimmed;

// 	trimmed = ft_strtrim("  \t\nHello, world!  \n\t", " \n\t");
// 	if (trimmed)
// 	{
// 		printf("Result: \"%s\"\n", trimmed);
// 		free(trimmed);
// 	}

// 	trimmed = ft_strtrim("xxx42xxx", "x");
// 	if (trimmed)
// 	{
// 		printf("Result: \"%s\"\n", trimmed);
// 		free(trimmed);
// 	}

// 	trimmed = ft_strtrim("Libft", "");
// 	if (trimmed)
// 	{
// 		printf("Result: \"%s\"\n", trimmed);
// 		free(trimmed);
// 	}

// 	return (0);
// }
