/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:03:40 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/08 15:37:12 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_sigint(int sig)
{
	char *cur_dir;

	(void)sig;
	g_info.kill = TRUE;
	ft_printf("\n");
	if (!(cur_dir = get_cur_dir()))
		cur_dir = ft_strdup("/");
	ft_printf(BLUE "~ %s > " RESET, cur_dir);
	get_pos(&g_info.cursor.start_posx, &g_info.cursor.start_posy);
	g_info.prompt_len = ft_strlen(cur_dir) + 6;
	if (cur_dir)
		free(cur_dir);
	cur_dir = NULL;
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
