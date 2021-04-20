/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:03:40 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/20 18:52:16 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_sigint(int sig)
{
	char *cur_dir;

	(void)sig;
	g_info->kill = TRUE;
	g_info->sig_status = 130;
	ft_printf("\n");
	if (!g_info->bin_running)
	{
		if (!(cur_dir = get_cur_dir()))
			cur_dir = ft_strdup("/");
		ft_printf(BLUE "~ %s > " RESET, cur_dir);
		g_info->prompt_len = ft_strlen(cur_dir) + 6;
		get_pos(&g_info->cursor.posx, &g_info->cursor.posy);
		if (cur_dir)
			free(cur_dir);
		cur_dir = NULL;
	}
}

void		ft_sigquit(int sig)
{
    (void)sig;
	g_info->sig_status = 131;
    write(2, "\b\b  ", 4);
    write(2, "\b\b", 2);
}
