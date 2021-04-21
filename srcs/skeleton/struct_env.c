/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 17:47:05 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/21 14:30:48 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*get_env_custom(char *key)
{
	t_list	*var_list;
	t_env	*var;
	t_env	*data_ref;

	data_ref = create_env_struct(key, NULL);
	var_list = ft_list_find(g_info->env_head, \
		data_ref, cmp_env);
	secure_free(data_ref);
	if (!var_list)
		return (NULL);
	var = (t_env *)var_list->data;
	return (var);
}

int	modify_env(char *key, char *new_value, int concat)
{
	t_env	*var;
	char	*tmp_value;

	var = get_env_custom(key);
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
