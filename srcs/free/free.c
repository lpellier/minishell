/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:39:00 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/29 13:09:29 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		free_tab(char **tab)
{
	int		i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i])
				free(tab[i]);
			tab[i] = NULL;
			i++;
		}
		free(tab);
	}
	tab = NULL;
}

void		free_cmd_struct(void *data)
{
	t_cmd	*ptr;

	ptr = (t_cmd *)data;
	ptr->bui = 9;
	if (ptr->cmd)
		free(ptr->cmd);
	ptr->cmd = NULL;
	if (ptr->input)
		free(ptr->input);
	ptr->input = NULL;
	if (ptr->option)
		free(ptr->option);
	ptr->option = NULL;
	if (ptr->path)
		free(ptr->path);
	ptr->path = NULL;
}

void		free_env_struct(void *data)
{
	t_env	*ptr;

	ptr = (t_env *)data;
	if (ptr->value)
		free(ptr->value);
	ptr->value = NULL;
	if (ptr->key)
		free(ptr->key);
	ptr->key = NULL;
}

void		free_history_struct(void *data)
{
    t_history	*ptr;

    ptr = (t_history *)data;
    ft_bzero(ptr->line, ft_strlen(ptr->line));
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void		ft_list_clear(t_list *begin_list, void (*free_fct)(void *))
{
	t_list	*ptr;

	while (begin_list)
	{
		ptr = begin_list->next;
		free_fct(begin_list->data);
		free(begin_list);
		begin_list = ptr;
	}
	begin_list = NULL;
}
