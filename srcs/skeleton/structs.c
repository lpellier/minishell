/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 15:12:16 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/08 13:44:15 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*get_env_custom(char *key)
{
	t_list	*var_list;
	t_env	*var;

	var_list = ft_list_find(g_info.env_head, create_env_struct(key, NULL), \
		cmp_env);
	if (!(var_list))
		return (NULL);
	var = (t_env *)var_list->data;
	return (var);
}

int	modify_env(char *key, char *new_value, int concat)
{
	t_env	*var;
	char	*tmp_value;

	var = get_env_custom(key);
	tmp_value = ft_strdup(var->value);
	secure_free(var->value);
	if (!concat)
		var->value = ft_strdup(new_value);
	else
		var->value = ft_strjoin(tmp_value, new_value);
	secure_free(tmp_value);
	return (SUCCESS);
}

/*
** mallocs and creates cmd struct, returns pointer on struct
*/

t_cmd	*create_cmd_struct(void)
{
	t_cmd	*cmd;

	if (ft_calloc((void **)&cmd, 1, sizeof(t_cmd)))
		return (NULL);
	cmd->bui = 9;
	cmd->cmd = NULL;
	cmd->input = NULL;
	cmd->option = NULL;
	cmd->path = NULL;
	return (cmd);
}

/*
** same as above for env struct
*/

t_env	*create_env_struct(char *key, char *value)
{
	t_env	*env;

	if (ft_calloc((void **)&env, 1, sizeof(t_env)))
		return (NULL);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	return (env);
}
