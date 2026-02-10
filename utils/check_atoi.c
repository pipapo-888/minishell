#include "../minishell.h"

long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	compare_digits(const char *str, const char *limit)
{
	int	s_len;
	int	l_len;

	s_len = ft_strlen(str);
	l_len = ft_strlen(limit);
	if (s_len > l_len || ft_strcmp(str, limit) > 0)
		return (1);
	return (0);
}

int	llong_check_atoi(const char *str)
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
		return (compare_digits(&str[i], L_LLONG_MAX));
	return (compare_digits(&str[i], L_LLONG_MIN));
}
