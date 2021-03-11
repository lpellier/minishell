/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:48:26 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/11 13:24:33 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		init(t_info *info, char **envp)
{
	init_built_in();
	info->crashed = FALSE;
	info->output = NULL;
	info->env_head = ft_create_elem(create_env_struct(NULL, NULL));
	init_env(info, envp);
	info->dir_paths = ft_split(((t_env *)ft_list_find(info->env_head,
		create_env_struct("PATH", "NULL"), cmp_env)->data)->value, ":");
	info->nb_colon = 0;
 	info->nb_l_redir = 0;
 	info->nb_pipe = 0;
 	info->nb_r_redir = 0;
 	info->nb_rd_redir = 0;
 }

 void reset_info(t_info *info)
 {
 	info->nb_colon = 0;
 	info->nb_l_redir = 0;
 	info->nb_pipe = 0;
 	info->nb_r_redir = 0;
 	info->nb_rd_redir = 0;
 }


/*
** signal(SIGQUIT, ft_sigquit); ctrl + \
** signal(SIGINT, ft_sigint); ctrl + c
** signal(SIGTERM, (void (*)(int))ft_sigterm); ctrl + d
*/

int			shell_loop(char **envp)
{
	t_info	info;
	char	*cur_dir;

	init(&info, envp);
	ft_printf(RED "Welcome to Minisheh\n" RESET);
	while (!info.crashed)
	{
		if (!(cur_dir = get_cur_dir(&info)))
			cur_dir = ft_strdup("/");
		ft_printf(BLUE "~ %s > " RESET, cur_dir);
		info.cmd_head = ft_create_elem(create_cmd_struct());
		read_line(&info);
		reset_info(&info);
		ft_list_clear(info.cmd_head, free_cmd_struct);
		ft_bzero(info.cur_path, 4096);
		free(cur_dir);
	}
	free_tab(info.dir_paths);
	ft_list_clear(info.env_head, free_env_struct);
	return (SUCCESS);
}

int			main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	system("clear");
	exit(shell_loop(envp));
}
