/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:48:26 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/30 17:12:47 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		update_cmd_status()
{
	t_env *data;

	data = (t_env *)info.env_head->data;
	if (data->value)
		free(data->value);
	data->value = ft_itoa(info.cmd_status);
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
	while (!info.crashed)
    {
		if (!(cur_dir = get_cur_dir()))
			cur_dir = ft_strdup("/");
		ft_printf(BLUE "~ %s > " RESET, cur_dir);
		get_pos(&info.cursor.start_posx, &info.cursor.start_posy);
		info.prompt_len = ft_strlen(cur_dir) + 6;
		info.cmd_head = ft_create_elem(create_cmd_struct());
		read_line(first);
		first = 0;
		reset_info();
		ft_list_clear(info.cmd_head, free_cmd_struct);
		ft_bzero(info.cur_path, ft_strlen(info.cur_path));
		free(cur_dir);
		cur_dir = NULL;
		update_cmd_status();
	}
	free_tab(&info.dir_paths);
	if (info.output)
		free(info.output);
	ft_list_clear(info.env_head, free_env_struct);
	ft_list_clear(info.history_head, free_history_struct);
	return (SUCCESS);
}

int			main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
    exit(shell_loop(envp));
}
