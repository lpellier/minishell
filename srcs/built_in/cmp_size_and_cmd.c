/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_size_and_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:29:21 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/25 16:02:26 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	compare_size(char *s1, char *s2)
{
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!ft_strncmp(s1, s2, len1) && len1 == len2)
		return (SUCCESS);
	else
		return (FAILURE);
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
		g_info->cmd_status = 127;
		update_cmd_status();
	}
}
