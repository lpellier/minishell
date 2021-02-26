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

t_cmd	*ft_create_elem(char *cmd, char *input, int bui, char *option)
{
	t_cmd *res;

	res = 0;
	if ((res = malloc(sizeof(t_cmd))))
	{
		res->cmd = cmd;
		res->input = input;
		res->bui = bui;
		res->option = option;
		res->next = 0;
	}
	return (res);
}

void	ft_list_push_front(t_cmd **list, char *cmd, char *input, int bui, char *option)
{
	t_cmd *elem;

	elem = ft_create_elem(cmd, input, bui, option);
	if (*list)
		elem->next = *list;
	*list = elem;
}

int		ft_list_size(t_cmd *list)
{
	t_cmd	*current;
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

t_cmd	*ft_list_last(t_cmd *list)
{
	t_cmd *current;

	current = list;
	while (current->next)
	{
		current = current->next;
	}
	return (current);
}

void	ft_list_push_back(t_cmd **begin_list, char *cmd, char *input, int bui, char *option)
{
	t_cmd *list;

	if (!(*begin_list))
	{
		*begin_list = ft_create_elem(cmd, input, bui, option);
		return ;
	}
	list = *begin_list;
	while (list->next)
		list = list->next;
	list->next = ft_create_elem(cmd, input, bui, option);
}

void	free_cmd(t_cmd *list)
{
	if (list->cmd)
		free(list->cmd);
	list->cmd = NULL;
	if (list->input)
		free(list->input);
	list->input = NULL;
	list->bui = 0;
	if (list->option)
		list->option = NULL;
	list->option = NULL;
}

void	ft_list_clear(t_cmd *begin_list)
{
	t_cmd	*ptr;

	while (begin_list)
	{
		ptr = begin_list->next;
		free_cmd(begin_list);
		free(begin_list);
		begin_list = ptr;
	}
	begin_list = 0;
}

t_cmd	*ft_list_at(t_cmd *begin_list, unsigned int nbr)
{
	t_cmd			*list;
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

void	ft_list_reverse(t_cmd **begin_list)
{
	t_cmd *prev;
	t_cmd *next;
	t_cmd *current;

	prev = 0;
	next = 0;
	current = *begin_list;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*begin_list = prev;
}

// NEEDS A FIND FUNCTION (MAYBE)
