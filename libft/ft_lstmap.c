/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 10:27:41 by lpellier          #+#    #+#             */
/*   Updated: 2019/11/25 14:11:06 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*newelem;

	if (!lst || !f)
		return (NULL);
	if (!f(lst->content))
		return (NULL);
	newlst = ft_lstnew(f(lst->content));
	newlst->next = NULL;
	if (!lst->next)
		return (newlst);
	lst = lst->next;
	while (lst)
	{
		if (!f(lst->content))
		{
			ft_lstclear(&newlst, *del);
			return (NULL);
		}
		newelem = ft_lstnew(f(lst->content));
		ft_lstadd_back(&newlst, newelem);
		lst = lst->next;
	}
	return (newlst);
}
