/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:03:40 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/07 15:22:48 by tefroiss         ###   ########.fr       */
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
//    ft_list_clear(info.cmd_head, free_cmd_struct);
//    ft_bzero(info.cur_path, 4096);
//    free_tab(info.dir_paths);
//    ft_list_clear(info.env_head, free_env_struct);
//    exit(1);
    ft_printf("exit\n");
    g_info.crashed = 1;
}
