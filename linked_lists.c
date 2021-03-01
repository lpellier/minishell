/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:00:49 by tefroiss          #+#    #+#             */
/*   Updated: 2021/02/25 1335:5:344 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_create_elem(void *data)
{
    t_list *res;

    if (!(res = (t_list *)malloc(sizeof(t_list))))
        return NULL;
    res->data = data;
    res->next = NULL;
    return (res);
}

void	ft_list_push_front(t_list **list, void *data)
{
    t_list *elem;

    elem = ft_create_elem(data);
    if (*list)
        elem->next = *list;
    *list = elem;
}

int		ft_list_size(t_list *list)
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

t_list	*ft_list_last(t_list *list)
{
    t_list *current;

    current = list;
    while (current->next)
    {
        current = current->next;
    }
    return (current);
}

void	ft_list_push_back(t_list **begin_list, void *data)
{
    t_list *list;

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

t_list	*ft_list_at(t_list *begin_list, unsigned int nbr)
{
    t_list			*list;
    unsigned int	i;

    i = 0;
    list = begin_list;
    while (i < nbr)
    {
        if (!list)
            return (0);
        list = list->next;
        i++;
    }
    return (list);
}

// NEEDS A FIND FUNCTION (MAYBE)
