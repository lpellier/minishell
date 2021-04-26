/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_cmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:26:38 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/26 23:40:59 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	cmp_env(void *data, void *data_ref)
{
	t_env	*env;
	t_env	*env_ref;

	env = (t_env *)data;
	env_ref = (t_env *)data_ref;
	if (!env || !env_ref)
		return (FAILURE);
	if (!(compare_size(env->key, env_ref->key)))
		return (SUCCESS);
	else
		return (FAILURE);
}

void	print_env_declare(void *data)
{
	t_env	*ptr;

	ptr = (t_env *)data;
	ft_printf("declare -x %s=\"%s\"\n", ptr->key, ptr->value);
}
