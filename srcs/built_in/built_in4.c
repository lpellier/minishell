/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 11:44:54 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/08 11:49:56 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**destroys a environment variable from memory
*/

int	ft_unset(int index_cmd)
{
	t_cmd	*cmd;

	cmd = ft_list_at(g_info.cmd_head, index_cmd)->data;
	if (cmd->option)
	{
		ft_printf("minisheh: %s: %s: invalid option\n", cmd->cmd, cmd->option);
		return (FAILURE);
	}
	if (!g_info.env_head || !g_info.env_head->next)
		return (FAILURE);
	ft_list_remove_if(&g_info.env_head->next,
		create_env_struct(cmd->input, NULL), cmp_env, free_env_struct);
	return (SUCCESS);
}

/*
** outputs all environment variables
*/

int	ft_env(int index_cmd)
{
	t_cmd	*cmd;

	cmd = ft_list_at(g_info.cmd_head, index_cmd)->data;
	if (cmd->option)
	{
		ft_printf("minisheh: %s: %s: invalid option\n", cmd->cmd, cmd->option);
		return (FAILURE);
	}
	if (!g_info.env_head || !g_info.env_head->next)
		return (FAILURE);
	ft_list_foreach(g_info.env_head->next, print_env_struct);
	return (SUCCESS);
}

/*
** this is used to count different arguments for binaries
** this WILL be tricky as we'll need to account for ""  and ''
** as a single argument
** and there might be backslashes canceling quotes -> it's going to be tough
*/

char	**count_args(t_cmd *cmd, int *count)
{
	char	**split;
	int		i;

	*count = 0;
	i = 0;
	if (cmd->input)
	{
		split = ft_split(cmd->input, ' ');
		while (split[i])
			i++;
		*count += i;
	}
	else
		split = NULL;
	if (cmd->cmd)
		*count += 1;
	if (cmd->option)
		*count += 1;
	return (split);
}

void	compare_cmd(t_cmd *cmd)
{
	if (!cmd->cmd)
		cmd->bui = NONEXISTENT;
	else if (!compare_size(cmd->cmd, "echo"))
		cmd->bui = ECHOO;
	else if (!compare_size(cmd->cmd, "exit"))
		cmd->bui = EXIT;
	else if (!compare_size(cmd->cmd, "pwd"))
		cmd->bui = PWD;
	else if (!compare_size(cmd->cmd, "export"))
		cmd->bui = EXPORT;
	else if (!compare_size(cmd->cmd, "unset"))
		cmd->bui = UNSET;
	else if (!compare_size(cmd->cmd, "env"))
		cmd->bui = ENV;
	else if (!compare_size(cmd->cmd, "cd"))
		cmd->bui = CD;
	else if (!find_binary(cmd))
		cmd->bui = BINARY;
	else
	{
		cmd->bui = NONEXISTENT;
		g_info.cmd_status = 127;
	}
}
