/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:21:31 by habe              #+#    #+#             */
/*   Updated: 2025/05/14 19:36:43 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*ans;
	long	nbr;
	int		len;

	nbr = (long)n;
	len = count_digits(nbr);
	ans = malloc(sizeof(char) * (len + 1));
	if (!ans)
		return (NULL);
	ans[len] = '\0';
	if (nbr < 0)
	{
		ans[0] = '-';
		nbr = -nbr;
	}
	else if (nbr == 0)
		ans[0] = '0';
	while (nbr > 0)
	{
		ans[len - 1] = (nbr % 10) + '0';
		nbr /= 10;
		len--;
	}
	return (ans);
}

// #include <stdio.h>
// #include <stdlib.h>

// char	*ft_itoa(int n);

// int	main(void)
// {
// 	char *str;

// 	str = ft_itoa(12345);
// 	if (str)
// 	{
// 		printf("Result: %s\n", str);
// 		free(str);
// 	}

// 	str = ft_itoa(-9876);
// 	if (str)
// 	{
// 		printf("Result: %s\n", str);
// 		free(str);
// 	}

// 	str = ft_itoa(0);
// 	if (str)
// 	{
// 		printf("Result: %s\n", str);
// 		free(str);
// 	}

// 	return (0);
// }
