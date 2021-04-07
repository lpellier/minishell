/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:03:40 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/07 17:26:41 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_sigint(int sig)
{
    (void)sig;
    write(0, "\n", 1);
    g_info.crashed = 2;
}

void		ft_sigquit(int sig)
{
    (void)sig;
    write(2, "\b\b  ", 4);
    write(2, "\b\b", 2);
}
void		ft_sigterm(int sig)
{
	(void)sig;
//    ft_list_clear(g_info.cmd_head, free_cmd_struct);
//    ft_bzero(g_info.cur_path, 4096);
//    free_tab(g_info.dir_paths);
//    ft_list_clear(g_info.env_head, free_env_struct);
//    exit(1);
    ft_printf("exit\n");
    g_info.crashed = 1;
}
