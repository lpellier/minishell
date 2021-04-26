/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 21:47:04 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/26 21:47:11 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_create_elem(void *data)
{
	t_list	*res;

	if (ft_calloc((void **)&res, 1, sizeof(t_list)))
		return (NULL);
	res->data = data;
	res->next = NULL;
	return (res);
}

void	ft_list_push_front(t_list **begin_list, void *data)
{
	t_list	*list;

	if (*begin_list)
	{
		list = ft_create_elem(data);
		list->next = *begin_list;
		*begin_list = list;
	}
	else
		*begin_list = ft_create_elem(data);
}

void	ft_list_push_back(t_list **begin_list, void *data)
{
	t_list	*list;

	if (!(*begin_list))
	{
		*begin_list = ft_create_elem(data);
		return ;
	}
	list = *begin_list;
	while (list->next)
		list = list->next;
	list->next = ft_create_elem(data);
}
