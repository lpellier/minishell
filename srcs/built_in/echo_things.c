/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:26:38 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/11 16:48:42 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	only_n(char *str)
{
	int		i;

	i = 0;
	if (str[i] != '-')
		return (FAILURE);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	ft_echo(t_info *info, t_cmd *cmd)
{
	int		arg_index;

	arg_index = cmd->arg_index + 1;
	if (cmd->args[arg_index] && !only_n(cmd->args[arg_index]))
		return (ft_echo_n(info, cmd));
	while (cmd->args && cmd->args[arg_index] && arg_index < cmd->limit_index)
	{
		ft_putstr_fd(cmd->args[arg_index], STDOUT_FILENO);
		if (arg_index < cmd->limit_index - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		arg_index++;
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
	info->terminfo.echo_padding_x = 0;
	return (SUCCESS);
}

// /*
// ** outputs input without \n
// */

// info->terminfo.echo_padding_x = padding; 
// 	->need to find a formula to adjust padding in case line is carried down

int	ft_echo_n(t_info *info, t_cmd *cmd)
{
	int		padding;
	int		arg_index;

	arg_index = cmd->arg_index + 1;
	padding = 0;
	while (cmd->args && cmd->args[arg_index] && \
		!only_n(cmd->args[arg_index]))
		arg_index++;
	while (cmd->args && cmd->args[arg_index] && arg_index < cmd->limit_index)
	{
		ft_putstr_fd(cmd->args[arg_index], STDOUT_FILENO);
		padding += ft_strlen(cmd->args[arg_index]);
		if (arg_index < cmd->limit_index - 1)
		{
			ft_putstr_fd(" ", STDOUT_FILENO);
			padding += 1;
		}
		arg_index++;
	}
	info->terminfo.echo_padding_x = padding;
	return (SUCCESS);
}
