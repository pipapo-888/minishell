/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <@student.42tokyo.jp>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:40:02 by habe              #+#    #+#             */
/*   Updated: 2025/05/15 15:13:23 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*p;

	i = 0;
	p = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			p = ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		p = ((char *)&s[i]);
	return (p);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char *text = "Hello, world!";
// 	char *result;

// 	result = ft_strrchr(text, 'o');
// 	if (result)
// 		printf("Found: %s\n", result);
// 	else
// 		printf("Not found\n");

// 	result = ft_strrchr(text, 'z');
// 	if (result)
// 		printf("Found: %s\n", result);
// 	else
// 		printf("Not found\n"); 

// 	result = ft_strrchr(text, '\0');
// 	if (result)
// 		printf("Found null terminator at: \"%s\"\n", result);
// 	else
// 		printf("Not found\n");

// 	return (0);
// }
