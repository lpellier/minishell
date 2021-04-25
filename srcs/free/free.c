/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:39:00 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/25 17:17:33 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char ***tab)
{
	int		i;
	char	**cpy;

	i = 0;
	cpy = *tab;
	if (!cpy)
		return ;
	while (cpy[i])
	{
		free(cpy[i]);
		cpy[i] = NULL;
		i++;
	}
	free(*tab);
	*tab = NULL;
}

void	free_cmd_struct(void *data)
{
	t_cmd	*ptr;

	ptr = (t_cmd *)data;
	if (!data || !ptr)
		return ;
	ptr->bui = 9;
	secure_free(ptr->cmd);
	secure_free(ptr->option);
	secure_free(ptr->input);
	secure_free(ptr->path);
	secure_free(ptr);
}

void	free_env_struct(void *data)
{
	t_env	*ptr;

	ptr = (t_env *)data;
	if (!ptr)
		return ;
	if (ptr->value)
		free(ptr->value);
	ptr->value = NULL;
	if (ptr->key)
		free(ptr->key);
	ptr->key = NULL;
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	free_history_struct(void *data)
{
	t_history	*ptr;

	ptr = (t_history *)data;
	if (!ptr)
		return ;
	secure_free(ptr->line);
	secure_free(ptr);
}

void	ft_list_clear(t_list *begin_list, void (*free_fct)(void *))
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
