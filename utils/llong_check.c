/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llong_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:07:34 by knomura           #+#    #+#             */
/*   Updated: 2026/02/14 15:07:35 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]) != 0)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 - (str[i] - '0');
		i++;
	}
	if (sign == 1)
		return (-result);
	return (result);
}

static int	compare_digits(const char *str, const char *limit)
{
	int	s_len;
	int	l_len;

	s_len = ft_strlen(str);
	l_len = ft_strlen(limit);
	if (s_len > l_len)
		return (1);
	if (s_len == l_len && ft_strcmp(str, limit) > 0)
		return (1);
	return (0);
}

int	llong_check(const char *str)
{
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	if (str[i] == '\0')
		return (0);
	if (sign == -1)
		return (compare_digits(&str[i], L_LLONG_MIN));
	return (compare_digits(&str[i], L_LLONG_MAX));
}
