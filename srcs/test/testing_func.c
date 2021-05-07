/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:45:07 by lpellier          #+#    #+#             */
/*   Updated: 2021/05/07 15:26:32 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	test(t_cmd *cmd, int arg_index)
// {
// 	int j;
	
// 	j = 0;
// 	ft_printf(" ");
// 	while (cmd->args[arg_index][j])
// 	{
// 		ft_printf(CYAN "%d" RESET, cmd->lint[arg_index][j]);
// 		j++;
// 	}
// 	ft_printf(" ");
// 	if (arg_index < cmd->arg_nbr - 1)
// 		ft_printf(RED " || " RESET);
// 	arg_index++;
// }

void	print_cmd_info(t_cmd *cmd)
{
	int		j;
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
	while (cmd->args && cmd->args[arg_index])
	{
		j = 0;
		ft_printf(" ");
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
	ft_printf("\n");
}
