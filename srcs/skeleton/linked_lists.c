/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:45:57 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/08 13:27:14 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	ft_list_size(t_list *list)
{
	t_list	*current;
	int		i;

	i = 0;
	current = list;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
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
