/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:27:56 by habe              #+#    #+#             */
/*   Updated: 2025/04/29 17:27:58 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_l;
	size_t	i;

	src_l = ft_strlen(src);
	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_l);
}

// int	main(void)
// {
// 	char	x[] = "Hello, World!";
// 	char	y[20];
// 	int		z;

// 	z = ft_strlcpy(y, x, 6);
// 	printf("文字数：%d\n", z);
// 	printf("コピー後：%s\n", y);
// 	return (0);
// }
