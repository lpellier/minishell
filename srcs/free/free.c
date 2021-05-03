/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:39:00 by lpellier          #+#    #+#             */
/*   Updated: 2021/05/03 11:32:33 by lpellier         ###   ########.fr       */
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

void	free_lint_tab(int arg_nbr, int ***tab)
{
	int		i;
	int		**cpy;

	i = 0;
	cpy = *tab;
	if (!cpy)
		return ;
	while (i < arg_nbr)
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
	free_lint_tab(ptr->arg_nbr, &ptr->lint);
	free_tab(&ptr->args);
	secure_free(ptr->path);
	secure_free(ptr->saved_env_arg);
	ptr->bui = 9;
	ptr->arg_nbr = 0;
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

