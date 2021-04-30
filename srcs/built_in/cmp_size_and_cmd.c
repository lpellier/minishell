/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_size_and_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:29:21 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/30 15:33:36 by lpellier         ###   ########.fr       */
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
	int		arg_index;

	arg_index = cmd->arg_index;
	if (!cmd->args || !cmd->args[arg_index])
		cmd->bui = NONEXISTENT;
	else if (!compare_size(cmd->args[arg_index], "echo"))
		cmd->bui = ECHOO;
	else if (!compare_size(cmd->args[arg_index], "exit"))
		cmd->bui = EXIT;
	else if (!compare_size(cmd->args[arg_index], "pwd"))
		cmd->bui = PWD;
	else if (!compare_size(cmd->args[arg_index], "export"))
		cmd->bui = EXPORT;
	else if (!compare_size(cmd->args[arg_index], "unset"))
		cmd->bui = UNSET;
	else if (!compare_size(cmd->args[arg_index], "env"))
		cmd->bui = ENV;
	else if (!compare_size(cmd->args[arg_index], "cd"))
		cmd->bui = CD;
	else if (!find_binary(info, cmd))
		cmd->bui = BINARY;
	else
		cmd->bui = NONEXISTENT;
}
