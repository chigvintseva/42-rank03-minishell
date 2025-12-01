/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:00:33 by achigvin          #+#    #+#             */
/*   Updated: 2025/05/24 19:00:34 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*newnode;
	void	*newcontent;

	if (!lst || !del || !f)
		return (NULL);
	new_list = NULL;
	while (lst != NULL)
	{
		newcontent = f(lst->content);
		newnode = ft_lstnew(newcontent);
		if (newnode == NULL)
		{
			del(newcontent);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, newnode);
		lst = lst->next;
	}
	return (new_list);
}
