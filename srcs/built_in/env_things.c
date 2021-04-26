/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_things.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:10:36 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/26 23:47:08 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**destroys a environment variable from memory
*/

int	ft_unset()
{
	// t_cmd	*cmd;
	// t_env	*data_ref;

	// cmd = ft_list_at(info->cmd_head, info->index_cmd)->data;
	// if (cmd->option)
	// 	return (print_error_option(cmd));
	// if (!info->env_head || !info->env_head->next)
	// 	return (FAILURE);
	// data_ref = create_env_struct(cmd->input, NULL);
	// ft_list_remove_if(&info->env_head->next, data_ref, cmp_env, \
	// 	free_env_struct);
	// secure_free(data_ref);
	return (SUCCESS);
}

// int	print_declare_env(void)
// {
// 	if (!info->env_head || !info->env_head->next)
// 		return (FAILURE);
// 	ft_list_foreach(info->env_head->next, print_env_declare);
// 	return (SUCCESS);
// }

// /*
// ** outputs all environment variables
// */

int	ft_env()
{
	// t_cmd	*cmd;

	// cmd = ft_list_at(info->cmd_head, info->index_cmd)->data;
	// if (cmd->option)
	// 	return (print_error_option(cmd));
	// if (!info->env_head || !info->env_head->next)
	// 	return (FAILURE);
	// ft_list_foreach(info->env_head->next, print_env_struct);
	return (SUCCESS);
}
