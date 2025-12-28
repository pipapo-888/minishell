/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:10:06 by habe              #+#    #+#             */
/*   Updated: 2025/05/14 19:18:49 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*new_node_p;
	void	*new_content;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	new_node_p = NULL;
	while (lst != NULL)
	{
		new_content = f(lst->content);
		node = ft_lstnew(new_content);
		if (node == NULL)
		{
			del(new_content);
			ft_lstclear(&new_node_p, del);
			return (NULL);
		}
		ft_lstadd_back(&new_node_p, node);
		lst = lst->next;
	}
	return (new_node_p);
}
