/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <@student.42tokyo.jp>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:13:16 by habe              #+#    #+#             */
/*   Updated: 2025/05/15 15:13:01 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ans;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	ans = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!ans)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ans[i] = f(i, s[i]);
		i++;
	}
	ans[i] = '\0';
	return (ans);
}

// #include <stdio.h>
// #include <stdlib.h>

// char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

// char	to_upper_even(unsigned int i, char c)
// {
// 	if (i % 2 == 0 && c >= 'a' && c <= 'z')
// 		return (c - 32);
// 	return (c);
// }

// int	main(void)
// {
// 	char *result = ft_strmapi("libft is cool", to_upper_even);

// 	if (result)
// 	{
// 		printf("Result: %s\n", result); // Result: LiBt Is CoOl
// 		free(result);
// 	}
// 	else
// 	{
// 		printf("ft_strmapi failed\n");
// 	}

// 	return (0);
// }
