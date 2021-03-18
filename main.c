/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:48:26 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/18 12:02:26 by lpellier         ###   ########.fr       */
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

void		init(t_info *info, char **envp)
{
	init_built_in();
	info->crashed = FALSE;
	info->output = NULL;
	info->cmd_status = 0;
	init_env(info, envp);
	ft_list_push_front(&info->env_head, create_env_struct(ft_strdup("?"),
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
	data->value = NULL;
	data->value = ft_itoa(info->cmd_status);
}

int	ft_putchar(int c)
{
	write(STDOUT_FILENO, &c, 1);
	return (SUCCESS);
}

char *tparm(char *str, ...);

void		testing(t_info *info)
{
	char *term;
	char *str;

	term = ((t_env *)ft_list_find(info->env_head, 
		create_env_struct("TERM", NULL), cmp_env)->data)->value;
	tgetent(NULL, term); // only needs to be called once
	str = tgetstr("cm", NULL); 
	tputs(tgoto(str, 18, 1), 1, ft_putchar);
	tputs("allo\n", 1, ft_putchar);
	// tparm(str, NULL, 5, 1);
	//tgoto(str, col, row)
}

int			shell_loop(char **envp)
{
	t_info	info;
	int		first;
	char	*cur_dir;

	init(&info, envp);
	first = 1;
	ft_printf(RED "Welcome to Minisheh\n" RESET);
	while (!info.crashed)
	{
		if (!(cur_dir = get_cur_dir(&info)))
			cur_dir = ft_strdup("/");
		ft_printf(BLUE "~ %s > " RESET, cur_dir);
		info.cmd_head = ft_create_elem(create_cmd_struct());
		read_line(&info, first);
		first = 0;
		// testing(&info);
		ft_list_clear(info.cmd_head, free_cmd_struct);
		ft_bzero(info.cur_path, 4096);
		free(cur_dir);
		cur_dir = NULL;
		update_cmd_status(&info);
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
	exit(shell_loop(envp));
}
