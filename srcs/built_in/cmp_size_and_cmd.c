/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_size_and_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:29:21 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/27 00:07:11 by lpellier         ###   ########.fr       */
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

void	compare_cmd(t_info *info, t_cmd *cmd)
{
	if (!cmd->args || !cmd->args[0])
		cmd->bui = NONEXISTENT;
	else if (!compare_size(cmd->args[0], "echo"))
		cmd->bui = ECHOO;
	else if (!compare_size(cmd->args[0], "exit"))
		cmd->bui = EXIT;
	else if (!compare_size(cmd->args[0], "pwd"))
		cmd->bui = PWD;
	else if (!compare_size(cmd->args[0], "export"))
		cmd->bui = EXPORT;
	else if (!compare_size(cmd->args[0], "unset"))
		cmd->bui = UNSET;
	else if (!compare_size(cmd->args[0], "env"))
		cmd->bui = ENV;
	else if (!compare_size(cmd->args[0], "cd"))
		cmd->bui = CD;
	else if (!find_binary(info, cmd))
		cmd->bui = BINARY;
	else
	{
		cmd->bui = NONEXISTENT;
		update_cmd_status(info, 127);
	}
}
