/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 15:12:16 by lpellier          #+#    #+#             */
/*   Updated: 2021/05/02 12:26:57 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** mallocs and creates cmd struct, returns pointer on struct
*/

t_cmd	*create_cmd_struct(void)
{
	t_cmd	*cmd;

	if (ft_calloc((void **)&cmd, 1, sizeof(t_cmd)))
		return (NULL);
	cmd->bui = 9;
	cmd->arg_nbr = 0;
	cmd->arg_index = 0;
	cmd->limit_index = 0;
	cmd->init_redir = FALSE;
	cmd->lint = NULL;
	cmd->args = NULL;
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
	env->key = key;
	env->value = value;
	return (env);
}

t_history	*create_history_struct(void)
{
	t_history	*history;

	if (ft_calloc((void **)&history, 1, sizeof(t_history)))
		return (NULL);
	if (ft_calloc((void **)&history->line, LINE_MAX, sizeof(char)))
		return (NULL);
	return (history);
}

