/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:54:17 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 13:54:18 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_words_in_str(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]) == 0 && \
				(ft_isspace(str[i + 1]) != 0 || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	count_total_words(t_token *tokens)
{
	int	total;

	total = 0;
	while (tokens != NULL && tokens->type == WORD)
	{
		if (tokens->split == 0 && ft_strchr(tokens->value, '=') == NULL)
			total += count_words_in_str(tokens->value);
		else
			total++;
		tokens = tokens->next;
	}
	return (total);
}

static int	split_word(t_cmd *cmd, t_token **tokens, int i)
{
	int		j;
	int		count;
	char	**split_words;

	split_words = space_tab_split((*tokens)->value);
	count = 0;
	if (split_words != NULL)
	{
		j = 0;
		while (split_words[j] != NULL)
		{
			cmd->argv[i++] = split_words[j];
			j++;
			count++;
		}
		free(split_words);
	}
	return (count);
}

void	put_in_word(t_cmd *cmd, t_token **tokens)
{
	int		i;

	cmd->argv = malloc(sizeof(char *) * (count_total_words(*tokens) + 1));
	if (cmd->argv == NULL)
		return ;
	i = 0;
	while (*tokens != NULL && (*tokens)->type == WORD)
	{
		if ((*tokens)->split == 0 && ft_strchr((*tokens)->value, '=') == NULL)
			i += split_word(cmd, tokens, i);
		else
			cmd->argv[i++] = ft_strdup((*tokens)->value);
		*tokens = (*tokens)->next;
	}
	cmd->argv[i] = NULL;
}
