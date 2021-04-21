/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 15:12:16 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/09 17:47:31 by tefroiss         ###   ########.fr       */
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

t_block	*create_block_struct(int a, int b)
{
	t_block	*block;

	if (ft_calloc((void **)&block, 1, sizeof(t_block)))
		return (NULL);
	block->start = a;
	block->end = b;
	return (block);
}
