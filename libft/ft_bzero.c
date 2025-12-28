/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <@student.42tokyo.jp>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:33:06 by habe              #+#    #+#             */
/*   Updated: 2025/05/15 15:10:13 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char buffer[10] = "abcdefghi";
// 	printf("Before: %s\n", buffer);

// 	ft_bzero(buffer + 2, 3);

// 	printf("After: ");
// 	for (int i = 0; i < 9; i++)
// 	{
// 		if (buffer[i] == '\0')
// 			printf("\\0");
// 		else
// 			printf("%c", buffer[i]);
// 	}
// 	printf("\n");

// 	return (0);
// }
