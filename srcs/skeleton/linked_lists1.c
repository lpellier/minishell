/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:25:35 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/08 13:27:14 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	print_env_struct(void *data)
{
	t_env	*ptr;

	ptr = (t_env *)data;
	ft_printf("%s=%s\n", ptr->key, ptr->value);
}

void	print_history(void *data)
{
	t_history	*ptr;

	ptr = (t_history *)data;
	ft_printf("%s\n", ptr->line);
}

void	ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
	t_list	*el;

	if (!begin_list)
		return ;
	el = begin_list;
	while (el)
	{
		f(el->data);
		el = el->next;
	}
}

int	cmp_env(void *data, void *data_ref)
{
	t_env	*env;
	t_env	*env_ref;

	env = (t_env *)data;
	env_ref = (t_env *)data_ref;
	if (!(compare_size(env->key, env_ref->key)))
		return (SUCCESS);
	else
		return (FAILURE);
}
