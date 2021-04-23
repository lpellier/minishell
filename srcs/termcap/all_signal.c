/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:03:40 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/23 16:15:26 by lpellier         ###   ########.fr       */
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
}

void	ft_sigquit(int sig)
{
	(void)sig;
	g_info->sig_status = 131;
	write(2, "\b\b  ", 4);
	write(2, "\b\b", 2);
}
