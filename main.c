/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:48:26 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/31 11:45:19 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history *create_history_struct(char *str)
{
    t_history *history;

    if (!(history = (t_history *)malloc(sizeof(t_history))))
        return (NULL);
    history->line = str;
    return (history);
}

void		update_cmd_status()
{
	t_env *data;

	data = ((t_env *)ft_list_find(info.env_head, create_env_struct("?", NULL), 
		cmp_env)->data);
	if (data->value)
		free(data->value);
	data->value = ft_itoa(info.cmd_status);
}

void		init(char **envp)
{
	init_built_in();
	info.crashed = FALSE;
	info.output = NULL;
	info.cmd_status = 0;
	init_env(envp);
	ft_list_push_front(&info.env_head, create_env_struct(ft_strdup("?"),
		ft_itoa(info.cmd_status)));
	info.dir_paths = ft_split(((t_env *)ft_list_find(info.env_head,
		create_env_struct("PATH", "NULL"), cmp_env)->data)->value, ":");
	info.nb_colon = 0;
	info.nb_l_redir = 0;
	info.nb_pipe = 0;
	info.nb_r_redir = 0;
	info.nb_rd_redir = 0;
	info.file_fd = -1;
}

void reset_info()
{	
	info.nb_colon = 0;
	info.nb_l_redir = 0;
	info.nb_pipe = 0;
	info.nb_r_redir = 0;
	info.nb_rd_redir = 0;
	info.file_fd = -1;
}

/* Functions for testing termcaps

void		update_cmd_status()
{
	t_env *data;

	data = ((t_env *)ft_list_find(info.env_head, create_env_struct("?", NULL), 
		cmp_env)->data);
	if (data->value)
		free(data->value);
	data->value = NULL;
	data->value = ft_itoa(info.cmd_status);
}

int	ft_putchar(int c)
{
	write(STDOUT_FILENO, &c, 1);
	return (SUCCESS);
}

char *tparm(char *str, ...);

void		testing()
{
	char *term;
	char *str;

	term = ((t_env *)ft_list_find(info.env_head, 
		create_env_struct("TERM", NULL), cmp_env)->data)->value;
	tgetent(NULL, term); // only needs to be called once
	str = tgetstr("cm", NULL); 
	tputs(tgoto(str, 18, 1), 1, ft_putchar);
	tputs("allo\n", 1, ft_putchar);
	// tparm(str, NULL, 5, 1);
	//tgoto(str, col, row)
}

*/

void		init_termcap()
{
	char *term;

	term = getenv("TERM");
	tgetent(NULL, term);
}

/*
** sole reason of first var is to create head of history linked list in read_line
*/

int			shell_loop()
{
	int		first;
	char	*cur_dir;

	first = 1;
	init_termcap();
    // signal(SIGQUIT, ft_sigquit);
    // signal(SIGTERM, ft_sigterm);
    // signal(SIGINT, ft_sigint);
	ft_printf(RED "Welcome to Minisheh\n" RESET);
	while (!info.crashed)
    {
		if (!(cur_dir = get_cur_dir()))
			cur_dir = ft_strdup("/");
		ft_printf(BLUE "~ %s > " RESET, cur_dir);
		info.cmd_head = ft_create_elem(create_cmd_struct());
		read_line(first);
		first = 0;
		reset_info();
		ft_list_clear(info.cmd_head, free_cmd_struct);
		ft_bzero(info.cur_path, 4096);
		free(cur_dir);
		cur_dir = NULL;
		update_cmd_status();
	}
	free_tab(info.dir_paths);
	if (info.output)
		free(info.output);
	// ft_list_foreach(info.history_head, print_history);
	ft_list_clear(info.env_head, free_env_struct);
	ft_list_clear(info.history_head, free_history_struct);
	return (SUCCESS);
}

int			main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
    system("clear");
    init(envp);
    exit(shell_loop());
}
