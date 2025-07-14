/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:47:00 by jholterh          #+#    #+#             */
/*   Updated: 2024/11/26 14:38:35 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*head;
	void	*proc_content;

	if (!f || !del || !lst)
		return (NULL);
	head = NULL;
	while (lst)
	{
		proc_content = f(lst->content);
		if (proc_content != NULL)
		{
			node = ft_lstnew(proc_content);
			if (!node)
			{
				del(proc_content);
				ft_lstclear(&head, del);
				return (NULL);
			}
			ft_lstadd_back(&head, node);
		}
		lst = lst->next;
	}
	return (head);
}
