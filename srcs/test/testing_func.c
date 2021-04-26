/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:45:07 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/27 00:35:49 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_cmd_info(t_cmd *cmd)
{
	int		i;
	
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		ft_printf(CYAN "'%s'" RESET, cmd->args[i]);
		if (i < cmd->arg_nbr - 1)
			ft_printf(RED " | " RESET);
		i++;
	}
	ft_printf(RED " | bui -> " RESET);
	ft_printf(CYAN "%d\n" RESET, cmd->bui);
}

/* 
** Functions for testing termcap
*/

// char *tparm(char *str, ...);

// void		testing()
// {
// 	char *str;

// 	str = tgetstr("cm", NULL); 
// 	tputs(tgoto(str, 18, 1), 1, ft_putchar);
// 	// tputs("allo\n", 1, ft_putchar);
// 	// tparm(str, NULL, 5, 1);
// 	//tgoto(str, col, row)
// }
