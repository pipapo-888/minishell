/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_tab_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:37:49 by habe              #+#    #+#             */
/*   Updated: 2025/09/24 16:23:58 by babe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static size_t	space_tab_check(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

static size_t	count_words(const char *str)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (space_tab_check(str[i]) == 0)
			if (space_tab_check(str[i + 1]) == 1 || str[i + 1] == '\0')
				count++;
		i++;
	}
	return (count);
}

static int	fill_words(char **result, const char *str, size_t word_count)
{
	size_t	start;
	size_t	end;
	size_t	i;

	end = 0;
	i = 0;
	while (i < word_count)
	{
		while (space_tab_check(str[end]) != 0 && str[end] != '\0')
			end++;
		start = end;
		while (space_tab_check(str[end]) == 0 && str[end] != '\0')
			end++;
		result[i] = ft_substr(str, start, end - start);
		if (result[i] == NULL)
		{
			free_split(result);
			return (1);
		}
		i++;
	}
	result[i] = NULL;
	return (0);
}

char	**space_tab_split(const char *str)
{
	char	**result;
	size_t	words;

	if (str == NULL)
		return (NULL);
	words = count_words(str);
	result = malloc(sizeof(char *) * (words + 1));
	if (result == NULL)
		return (NULL);
	if (fill_words(result, str, words) != 0)
	{
		free_split(result);
		return (NULL);
	}
	return (result);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	char	**result;
// 	int		i = 0;

// 	result = space_tab_split("ls -l");

// 	if (!result)
// 		return (1);

// 	while (result[i])
// 	{
// 		printf("result[%d]: %s\n", i, result[i]);
// 		free(result[i]);
// 		i++;
// 	}
// 	free(result);

// 	return (0);
// }

// result[0]: Hello
// result[1]: world
// result[2]: from
// result[3]: 42
