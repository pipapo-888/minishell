/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:13:03 by habe              #+#    #+#             */
/*   Updated: 2025/05/14 19:46:27 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static void	free_split(char **ans, int i)
{
	while (i >= 0)
	{
		free(ans[i]);
		i--;
	}
	free(ans);
}

static int	fill_words(char **ans, char const *s, char c, size_t word_count)
{
	size_t	start;
	size_t	end;
	size_t	i;

	end = 0;
	i = 0;
	while (i < word_count)
	{
		while (s[end] == c)
			end++;
		start = end;
		while (s[end] != '\0' && s[end] != c)
			end++;
		ans[i] = ft_substr(s, start, end - start);
		if (ans[i] == NULL)
		{
			free_split(ans, i - 1);
			return (1);
		}
		i++;
	}
	ans[i] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**ans;
	size_t	word_count;

	if (s == NULL)
		return (NULL);
	word_count = count_words(s, c);
	ans = malloc(sizeof(char *) * (word_count + 1));
	if (ans == NULL)
		return (NULL);
	if (fill_words(ans, s, c, word_count) != 0)
		return (NULL);
	return (ans);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	char	**result;
// 	int		i = 0;

// 	result = ft_split("Hello world from 42", ' ');

// 	if (!result)
// 		return (1);

// 	while (result[i])
// 	{
// 		printf("result[%d]: %s\n", i, result[i]);
// 		free(result[i]);
// 		i++;
// 	}
// 	free(result);

// 	// 出力例:
// 	// result[0]: Hello
// 	// result[1]: world
// 	// result[2]: from
// 	// result[3]: 42

// 	return (0);
// }
