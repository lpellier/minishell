/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:45:07 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/09 14:35:44 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_cmd_info(t_cmd *cmd)
{
	ft_printf(CYAN "'%s'" RESET, cmd->cmd);
	ft_printf(RED " | " RESET);
	ft_printf(CYAN "'%s'" RESET, cmd->option);
	ft_printf(RED " | " RESET);
	ft_printf(CYAN "'%s'" RESET, cmd->input);
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
