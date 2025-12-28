/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:05:58 by habe              #+#    #+#             */
/*   Updated: 2025/05/14 20:14:52 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char *text = "Hello, world!";
// 	char *result;

// 	result = ft_strchr(text, 'w');
// 	if (result)
// 		printf("Found: %s\n", result); // Found: world!
// 	else
// 		printf("Not found\n");

// 	result = ft_strchr(text, 'z');
// 	if (result)
// 		printf("Found: %s\n", result);
// 	else
// 		printf("Not found\n"); // Not found

// 	result = ft_strchr(text, '\0');
// 	if (result)
// 		printf("Found null terminator at: \"%s\"\n", result);
// 	else
// 		printf("Not found\n");

// 	return (0);
// }
