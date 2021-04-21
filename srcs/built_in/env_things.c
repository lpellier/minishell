/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_things.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:10:36 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/21 14:30:48 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**destroys a environment variable from memory
*/

int	ft_unset(int index_cmd)
{
	t_cmd	*cmd;
	t_env	*data_ref;

	cmd = ft_list_at(g_info->cmd_head, index_cmd)->data;
	if (cmd->option)
	{
		ft_printf("minisheh: %s: %s: invalid option\n", cmd->cmd, cmd->option);
		return (FAILURE);
	}
	if (!g_info->env_head || !g_info->env_head->next)
		return (FAILURE);
	data_ref = create_env_struct(cmd->input, NULL);
	ft_list_remove_if(&g_info->env_head->next, data_ref, cmp_env, \
		free_env_struct);
	secure_free(data_ref);
	return (SUCCESS);
}

int	print_declare_env(void)
{
	if (!g_info->env_head || !g_info->env_head->next)
		return (FAILURE);
	ft_list_foreach(g_info->env_head->next, print_env_declare);
	return (SUCCESS);
}

/*
** outputs all environment variables
*/

int	ft_env(int index_cmd)
{
	t_cmd	*cmd;

	cmd = ft_list_at(g_info->cmd_head, index_cmd)->data;
	if (cmd->option)
	{
		ft_printf("minisheh: %s: %s: invalid option\n", cmd->cmd, cmd->option);
		return (FAILURE);
	}
	if (!g_info->env_head || !g_info->env_head->next)
		return (FAILURE);
	ft_list_foreach(g_info->env_head->next, print_env_struct);
	return (SUCCESS);
}
