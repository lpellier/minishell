/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:45:07 by lpellier          #+#    #+#             */
/*   Updated: 2021/05/10 14:10:28 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	testing_suite(t_cmd *cmd, int arg_index)
{
	int	j;

	while (cmd->args && cmd->args[arg_index])
	{
		ft_printf(" ");
		j = 0;
		while (cmd->args[arg_index][j])
		{
			ft_printf(CYAN "%d" RESET, cmd->lint[arg_index][j]);
			j++;
		}
		ft_printf(" ");
		if (arg_index < cmd->arg_nbr - 1)
			ft_printf(RED " || " RESET);
		arg_index++;
	}
}

void	print_cmd_info(t_cmd *cmd)
{
	int		arg_index;

	arg_index = cmd->arg_index;
	while (cmd->args && cmd->args[arg_index])
	{
		ft_printf(CYAN "'%s'" RESET, cmd->args[arg_index]);
		if (arg_index < cmd->arg_nbr - 1)
			ft_printf(RED " || " RESET);
		arg_index++;
	}
	ft_printf(RED " || nbr -> " RESET);
	ft_printf(CYAN "%d\n" RESET, cmd->arg_nbr);
	arg_index = cmd->arg_index;
	testing_suite(cmd, arg_index);
	ft_printf("\n");
}
