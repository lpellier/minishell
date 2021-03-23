/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:03:40 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/23 10:51:20 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info info;

/*
 * ctrl c
 */

void	ft_sigint(int sig)
{
    (void)sig;
    write(0, "\n", 1);
//    ft_printf("%s\n%s\n%s\n%d\n%d\n%d\n%d\n%d\n%d\n", info.output, info.dir_paths, info.envp, info.crashed, info.nb_colon, info.nb_l_redir, info.nb_pipe, info.nb_rd_redir, info.nb_r_redir);
//    ft_list_clear(info.cmd_head, free_cmd_struct);
//    ft_bzero(info.cur_path, 4096);
//    free_tab(info.dir_paths);
//    ft_list_clear(info.env_head, free_env_struct);
    if (wait(&info.crashed) < 0 && !WIFSIGNALED(info.crashed))
        shell_loop(&info);
    else
        info.crashed = 0;
}

/*
 * ctrl \
 */

void		ft_sigquit(int sig)
{
    (void)sig;
    write(2, "\b\b  ", 4);
    write(2, "\b\b", 2);
}

/*
 * ctrl d
 */

void		ft_sigterm(int sig)
{
	(void)sig;
//    ft_list_clear(info.cmd_head, free_cmd_struct);
//    ft_bzero(info.cur_path, 4096);
//    free_tab(info.dir_paths);
//    ft_list_clear(info.env_head, free_env_struct);
//    exit(1);
    ft_printf("exit\n");
    info.crashed = 1;
}
