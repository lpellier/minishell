/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:48:26 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/08 15:10:38 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			rem_hist(void *data, void *data_ref)
{
	t_history *ptr;
	(void)		data_ref;

	ptr = (t_history *)data;
	if (!ptr->line || !ptr->line[0])
		return (SUCCESS);
	return (FAILURE);
}

void		remove_useless_history()
{
	ft_list_remove_if(&g_info.history_head, NULL, rem_hist, free_history_struct);
}

void		update_cmd_status()
{
	t_env *data;

	data = (t_env *)g_info.env_head->data;
	if (data->value)
		free(data->value);
	data->value = NULL;
	data->value = ft_itoa(g_info.cmd_status);
}

/*
** sole reason of first var is to create head of history linked list in read_line
*/

int			shell_loop(char **envp)
{
	int		first;
	char	*cur_dir;

	first = 1;
	init_info(envp);
	init_termcap();
	ft_printf(RED "Welcome to Minisheh\n" RESET);
	while (!g_info.crashed)
    {
		if (!(cur_dir = get_cur_dir()))
			cur_dir = ft_strdup("/");
		ft_printf(BLUE "~ %s > " RESET, cur_dir);
		get_pos(&g_info.cursor.start_posx, &g_info.cursor.start_posy);
		g_info.prompt_len = ft_strlen(cur_dir) + 6;
		g_info.cmd_head = ft_create_elem(create_cmd_struct());
		read_line(first);
		first = 0;
		reset_info();
		ft_list_clear(g_info.cmd_head, free_cmd_struct);
		ft_bzero(g_info.cur_path, ft_strlen(g_info.cur_path));
		free(cur_dir);
		cur_dir = NULL;
		update_cmd_status();
		remove_useless_history();
	}
	free_tab(&g_info.dir_paths);
	if (g_info.output)
		free(g_info.output);
	ft_list_clear(g_info.env_head, free_env_struct);
	ft_list_clear(g_info.history_head, free_history_struct);
	ft_list_clear(g_info.block_head, free);
	return (SUCCESS);
}

int			main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, ft_sigint);
    exit(shell_loop(envp));
}
