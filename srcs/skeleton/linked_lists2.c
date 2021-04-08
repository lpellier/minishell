/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:25:31 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/08 13:27:14 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_list_find(t_list *begin_list, void *data_ref, int (*cmp)())
{
	t_list	*el;

	el = begin_list;
	while (el)
	{
		if (cmp(el->data, data_ref) == 0)
			return (el);
		el = el->next;
	}
	return (NULL);
}

void	ft_list_remove_if(t_list **begin_list, void *data_ref,
				int (*cmp)(), void (*free_fct)(void *))
{
	t_list	*tmp;
	t_list	*el;

	while (*begin_list && !cmp((*begin_list)->data, data_ref))
	{
		tmp = *begin_list;
		*begin_list = (*begin_list)->next;
		free_fct(tmp->data);
		free(tmp);
		tmp = NULL;
	}
	el = *begin_list;
	while (el && el->next)
	{
		if (!cmp(el->next->data, data_ref))
		{
			tmp = el->next;
			el->next = tmp->next;
			free_fct(tmp->data);
			free(tmp);
			tmp = NULL;
		}
		el = el->next;
	}
}
