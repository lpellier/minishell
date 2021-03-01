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
            return (NULL);
        list = list->next;
        i++;
    }
    return (list);
}

void    print_env_struct(void *data)
{
    t_env *ptr;

    ptr = (t_env *)data;
    ft_printf("%s=%s\n", ptr->key, ptr->value);
}

void	ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
    t_list *el;

    if (!begin_list)
        return ;
    el = begin_list;
    while (el)
    {
        f(el->data);
        el = el->next;
    }
}

int     cmp_env(void *data, void *data_ref)
{
    t_env *env;
    t_env *env_ref;

    env = (t_env *)data;
    env_ref = (t_env *)data_ref;

    if (!(ft_strncmp(env->key, env_ref->key, ft_strlen(env_ref->key))))
        return (0);
    else
        return (1);
}

/*t_list	*ft_list_find(t_list *begin_list, void *data_ref, int (*cmp)())
{
    t_list *el;

    el = begin_list;
    while (el)
    {
        if (cmp(el->data, data_ref) == 0)
            return (el);
        el = el->next;
    }
    return (NULL);
}*/

void	ft_list_remove_if(t_list **begin_list, void *data_ref,
                          int (*cmp)(), void (*free_fct)(void *))
{
    t_list	*tmp;
    t_list	*el;

    while (*begin_list && cmp((*begin_list)->data, data_ref) == 0)
    {
        tmp = *begin_list;
        *begin_list = (*begin_list)->next;
        free_fct(tmp->data);
        free(tmp);
    }
    el = *begin_list;
    while (el && el->next)
    {
        if (cmp(el->next->data, data_ref) == 0)
        {
            tmp = el->next;
            el->next = tmp->next;
            free_fct(tmp->data);
            free(tmp);
        }
        el = el->next;
    }
}