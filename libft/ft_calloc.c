/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:14:15 by habe              #+#    #+#             */
/*   Updated: 2025/05/14 19:35:19 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ans;
	size_t	total_size;

	if (nmemb == 0 || size == 0)
	{
		ans = malloc(0);
		return (ans);
	}
	if (nmemb > __SIZE_MAX__ / size)
		return (NULL);
	total_size = nmemb * size;
	ans = malloc(total_size);
	if (ans == NULL)
		return (NULL);
	ft_bzero(ans, total_size);
	return (ans);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	size_t	n = 5;
// 	int		*arr = ft_calloc(n, sizeof(int));
// 	if (!arr)
// 	{
// 		printf("ft_calloc failed\n");
// 		return (1);
// 	}

// 	for (size_t i = 0; i < n; i++)
// 		printf("%d ", arr[i]);
// 	printf("\n");

// 	free(arr);
// 	return (0);
// }
