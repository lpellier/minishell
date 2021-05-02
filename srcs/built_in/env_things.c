/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_things.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:10:36 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/02 19:05:38 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**destroys a environment variable from memory
*/

int	ft_unset(t_info *info, t_cmd *cmd)
{
	t_env	*data_ref;
	int		arg_index;

	arg_index = cmd->arg_index + 1;
	if (!arg_is_option(cmd->args[arg_index]))	
		return (print_error(cmd->args[arg_index - 1], \
			cmd->args[arg_index], "invalid option", 1));
	if (!info->env_head || !info->env_head->next)
		return (FAILURE);
	while (cmd->args && cmd->args[arg_index] && arg_index < cmd->limit_index)
	{
		data_ref = create_env_struct(cmd->args[arg_index], NULL);
		ft_list_remove_if(&info->env_head->next, data_ref, cmp_env, \
			free_env_struct);
		secure_free(data_ref);
		arg_index++;
	}
	reset_dir_paths(info);
	return (SUCCESS);
}



// /*
// ** outputs all environment variables
// */

int	ft_env(t_info *info, t_cmd *cmd)
{
	int		arg_index;

	arg_index = cmd->arg_index + 1;
	if (!arg_is_option(cmd->args[arg_index]))	
		return (print_error(cmd->args[arg_index - 1], \
			cmd->args[arg_index], "invalid option", 1));
	if (!info->env_head || !info->env_head->next)
		return (FAILURE);
	if (cmd->args && cmd->args[arg_index])
		return (print_error(NULL, cmd->args[arg_index], \
			"no such file or directory", 1));
	ft_list_foreach(info->env_head->next, print_env_struct);
	return (SUCCESS);
}
