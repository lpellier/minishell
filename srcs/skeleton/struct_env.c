/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 17:47:05 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/26 23:31:13 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*get_env_custom(t_info *info, char *key)
{
	t_list	*var_list;
	t_env	*var;
	t_env	*data_ref;

	data_ref = create_env_struct(key, NULL);
	var_list = ft_list_find(info->env_head, \
		data_ref, cmp_env);
	secure_free(data_ref);
	if (!var_list)
		return (NULL);
	var = (t_env *)var_list->data;
	return (var);
}

int	modify_env(t_info *info, char *key, char *new_value, int concat)
{
	t_env	*var;
	char	*tmp_value;

	var = get_env_custom(info, key);
	if (!var)
		return (FAILURE);
	tmp_value = ft_strdup(var->value);
	if (var->value)
		free(var->value);
	var->value = NULL;
	if (!concat)
		var->value = ft_strdup(new_value);
	else
		var->value = ft_strjoin(tmp_value, new_value);
	if (tmp_value)
		free(tmp_value);
	return (SUCCESS);
}
