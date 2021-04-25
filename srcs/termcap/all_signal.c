/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:03:40 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/25 14:01:57 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_sigint(int sig)
{
	(void)sig;
	g_info->kill = TRUE;
	g_info->sig_status = 130;
	ft_printf("\n");
	if (!g_info->bin_running)
		print_prompt();
	update_cmd_status();
}

void	ft_sigquit(int sig)
{
	(void)sig;
	g_info->sig_status = 131;
	write(2, "\b\b  ", 4);
	write(2, "\b\b", 2);
	update_cmd_status();
}
