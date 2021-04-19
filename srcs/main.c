/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:48:26 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/19 14:25:38 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			rem_hist(void *data, void *data_ref)
{
	t_history *ptr;
	(void)		data_ref;

	ptr = (t_history *)data;
	if (!ptr || !ptr->line || (ptr->line && !ptr->line[0]))
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
	secure_free(data->value);
	if (g_info.sig_status)
		data->value = ft_itoa(g_info.sig_status);
	else
		data->value = ft_itoa(g_info.cmd_status);
}

/*
** sole reason of first var is to create head of history linked list in read_line
*/

int			shell_loop()
{
	int		first;
	char	*cur_dir;

	first = 1;
	ft_printf(RED "Welcome to Minisheh\n" RESET);
	while (!g_info.crashed)
    {
		if (!(cur_dir = get_cur_dir()))
			cur_dir = ft_strdup("/");
		ft_printf(BLUE "~ %s > " RESET, cur_dir);
		get_pos(&g_info.cursor.start_posx, &g_info.cursor.start_posy);
		g_info.prompt_len = ft_strlen(cur_dir) + 6;
		g_info.cmd_head = ft_create_elem(create_cmd_struct());
		process_line(first);
		first = 0;
		secure_free(cur_dir);
		ft_list_clear(g_info.cmd_head, free_cmd_struct);
		ft_bzero(g_info.cur_path, ft_strlen(g_info.cur_path));
		update_cmd_status();
		reset_info();
		remove_useless_history();
	}
	secure_free(g_info.line);
	free_tab(&g_info.dir_paths);
	ft_list_clear(g_info.env_head, free_env_struct);
	ft_list_clear(g_info.history_head, free_history_struct);
	ft_list_clear(g_info.block_head, free);
	return (SUCCESS);
}

int			check_exec_options(int argc, char **argv)
{
	if (argc == 1)
		g_info.debug_option = FALSE;
	else if (argc == 2 && !compare_size(argv[1], "-d"))
		g_info.debug_option = TRUE;
	else if (argc >= 3)
	{
		ft_printf("Too many arguments. Minishell only supports one option (-d).\n");
		return (FAILURE);
	}
	else
	{
		ft_printf("Only one argument is currently supported : '-d'. It's there to help debugging.\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int			main(int argc, char **argv, char **envp)
{
	if (check_exec_options(argc, argv))
		exit(FAILURE);
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
	tgetent(NULL, getenv("TERM"));
	tcgetattr(STDOUT_FILENO, &g_info.termios_p);
	tcgetattr(STDOUT_FILENO, &g_info.saved_term);
	g_info.termios_p.c_lflag &= ~(ICANON | ECHO);
    g_info.termios_p.c_cc[VTIME] = 0;
    g_info.termios_p.c_cc[VMIN] = 1;
	g_info.cursor.col = tgetnum("co");
	g_info.cursor.lin = tgetnum("li");
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	if (init_info(envp))
		exit(EXIT_FAILURE);
	init_termcap();
    exit(shell_loop());
}
