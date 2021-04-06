/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 15:12:16 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/06 14:52:23 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*get_env_custom(char *key)
{
	t_list	*var_list;
	t_env	*var;

	if (!(var_list = ft_list_find(info.env_head, create_env_struct(key, NULL), cmp_env)))
		return (NULL);
	var = (t_env *)var_list->data;
	return (var);
}

int		modify_env(char *key, char *new_value, int concat)
{
	t_env	*var;
	char	*tmp_value;

	var = get_env_custom(key);
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

/*
** mallocs and creates cmd struct, returns pointer on struct
*/

t_cmd		*create_cmd_struct(void)
{
	t_cmd	*cmd;

	if (!(cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd))))
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

t_env		*create_env_struct(char *key, char *value)
{
	t_env	*env;

	if (!(env = (t_env *)ft_calloc(1, sizeof(t_env))))
		return (NULL);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	return (env);
}

t_history *create_history_struct()
{
    t_history *history;

    if (!(history = (t_history *)ft_calloc(1, sizeof(t_history))))
		return (NULL);
	history->line = ft_calloc(LINE_MAX, sizeof(char));
    return (history);
}
