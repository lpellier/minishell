/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:48:26 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/11 11:49:46 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		init(t_info *info, char **envp)
{
	init_built_in();
	info->crashed = FALSE;
	info->output = NULL;
	info->cmd_status = 0;
	info->env_head = ft_create_elem(create_env_struct(NULL, NULL));
	init_env(info, envp);
	ft_list_push_front(&info->env_head->next, create_env_struct(ft_strdup("?"),
		ft_itoa(info->cmd_status)));
	info->dir_paths = ft_split(((t_env *)ft_list_find(info->env_head,
		create_env_struct("PATH", "NULL"), cmp_env)->data)->value, ":");
}

/*
** signal(SIGQUIT, ft_sigquit); ctrl + \
** signal(SIGINT, ft_sigint); ctrl + c
** signal(SIGTERM, (void (*)(int))ft_sigterm); ctrl + d
*/

void		update_cmd_status(t_info *info)
{
	t_env *data;

	data = ((t_env *)ft_list_find(info->env_head, create_env_struct("?", NULL), 
		cmp_env)->data);
	if (data->value)
		free(data->value);
	data->value = ft_itoa(info->cmd_status);
}

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
		ft_list_clear(info.cmd_head, free_cmd_struct);
		ft_bzero(info.cur_path, 4096);
		free(cur_dir);
		update_cmd_status(&info);
	}
	free_tab(info.dir_paths);
	if (info.output)
		free(info.output);
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
