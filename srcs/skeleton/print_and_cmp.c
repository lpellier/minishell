/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_cmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:26:38 by tefroiss          #+#    #+#             */
/*   Updated: 2021/06/08 14:37:40 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env_struct(void *data)
{
	t_env	*ptr;

	ptr = (t_env *)data;
	ft_putstr_fd(ptr->key, STDOUT_FILENO);
	ft_putstr_fd("=", STDOUT_FILENO);
	if (ptr->value)
		ft_putstr_fd(ptr->value, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
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

char	**list_to_char(t_list *head, int len)
{
	int		i;
	t_env	*cur;
	char	**ret;

	i = 0;
	if (ft_calloc((void **)&ret, len, sizeof(char *)))
		return (NULL);
	while (i < len)
	{
		cur = ft_list_at(head, i)->data;
		ret[i] = ft_strdup(cur->key);
		i++;
	}
	return (ret);
}

char	**ascii_sort(t_list *head, int len)
{
	int		i;
	int		j;
	char	*tmp;
	char	**keys;

	i = 0;
	keys = list_to_char(head, len);
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(keys[j], keys[i], ft_strlen(keys[j])) < 0)
			{
				tmp = keys[i];
				keys[i] = keys[j];
				keys[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (keys);
}

void	print_env_declare(void *data)
{
	t_env	*ptr;

	ptr = (t_env *)data;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(ptr->key, STDOUT_FILENO);
	ft_putstr_fd("=", STDOUT_FILENO);
	ft_putstr_fd("\"", STDOUT_FILENO);
	ft_putstr_fd(ptr->value, STDOUT_FILENO);
	ft_putstr_fd("\"\n", STDOUT_FILENO);
}
