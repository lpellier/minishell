/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:45:07 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/28 16:02:16 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_cmd_info(t_cmd *cmd)
{
	int		arg_index;
	int		limit;

	arg_index = 0;
	if (cmd->recursive_index)
		arg_index = cmd->recursive_index + 1;
	if (cmd->next_pipe)
		limit = cmd->next_pipe;
	else
		limit = cmd->arg_nbr;
	while (cmd->args && cmd->args[arg_index] && arg_index < limit)
	{
		ft_printf(CYAN "'%s'" RESET, cmd->args[arg_index]);
		if (arg_index < limit - 1)
			ft_printf(RED " || " RESET);
		arg_index++;
	}
	ft_printf(RED " || nbr -> " RESET);
	ft_printf(CYAN "%d\n" RESET, cmd->arg_nbr);
	arg_index = 0;
	int		j;
	if (cmd->recursive_index)
		arg_index = cmd->recursive_index + 1;
	while (cmd->args && cmd->args[arg_index] && arg_index < limit)
	{
		j = 0;
		ft_printf(" ");
		while (cmd->args[arg_index][j])
		{
			ft_printf(CYAN "%d" RESET, cmd->lint[arg_index][j]);
			j++;
		}
		ft_printf(" ");
		if (arg_index < limit - 1)
			ft_printf(RED " || " RESET);
		arg_index++;
	}
	ft_printf("\n");
}
