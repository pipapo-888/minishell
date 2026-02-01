#include "../minishell.h"

static size_t	count_words(const char *str)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]) == 0 && \
			(ft_isspace(str[i + 1]) != 0 || str[i + 1] == '\0'))
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
		while (ft_isspace(str[end]) != 0 && str[end] != '\0')
			end++;
		start = end;
		while (ft_isspace(str[end]) == 0 && str[end] != '\0')
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
