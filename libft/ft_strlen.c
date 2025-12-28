/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:50:23 by habe              #+#    #+#             */
/*   Updated: 2025/04/29 13:39:54 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *c)
{
	size_t	length;

	length = 0;
	while (c[length] != '\0')
	{
		length++;
	}
	return (length);
}

// int	main(void)
// {
// 	char	a;

// 	a = "tokyo";
// 	printf("%d\n", ft_strlen(a));
// 	return (0);
// }
