/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:48:26 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/25 14:15:30 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_error_option(t_cmd *cmd)
{
	ft_printf("minisheh: %s: %s: invalid option\n", cmd->cmd, cmd->option);
	return (FAILURE);
}

int	print_error(char *error)
{
	ft_printf("%s\n", error);
	return (FAILURE);
}

int	rem_hist(void *data, void *data_ref)
{
	t_history	*ptr;

	(void) data_ref;
	ptr = (t_history *)data;
	if (!ptr || !ptr->line || (ptr->line && !ptr->line[0]))
		return (SUCCESS);
	return (FAILURE);
}

void	remove_useless_history(void)
{
	ft_list_remove_if(&g_info->history_head, NULL, rem_hist, \
		free_history_struct);
}

void	update_cmd_status(void)
{
	t_env	*data;

	data = (t_env *)g_info->env_head->data;
	secure_free(data->value);
	if (g_info->sig_status)
		data->value = ft_itoa(g_info->sig_status);
	else
		data->value = ft_itoa(g_info->cmd_status);
	g_info->cmd_status = 0;
	g_info->sig_status = 0;
}

void	print_prompt()
{
	char	*cur_dir;
	char	*strjoin;
	char	*prompt;

	cur_dir = get_cur_dir();
	if (!(cur_dir))
		cur_dir = ft_strdup("/");
	strjoin = ft_strjoin("\033[34m~ ", cur_dir);
	prompt = ft_strjoin(strjoin, " > \x1b[0m");
	secure_free(strjoin);
	ft_putstr_fd(prompt, STDERR_FILENO);
	secure_free(prompt);
	g_info->prompt_len = ft_strlen(cur_dir) + 5;
	g_info->cursor.posx = g_info->prompt_len + g_info->echo_padding;
	secure_free(cur_dir);
}

/*
** sole reason of first var is to create head of history linked list in read_line
*/

int	shell_loop(void)
{
	int		first;

	first = TRUE;
	ft_putstr_fd("\033[31mWelcome to Minisheh\n\x1b[0m", STDERR_FILENO);
	while (!g_info->crashed)
	{
		print_prompt();
		process_line(first);
		first = FALSE;
		reset_info();
		remove_useless_history();
	}
	free_blocks(g_info->block_head);
	free_tab(&g_info->dir_paths);
	secure_free(g_info->line);
	ft_list_clear(g_info->env_head, free_env_struct);
	ft_list_clear(g_info->history_head, free_history_struct);
	secure_free(g_info);
	return (SUCCESS);
}

int	check_exec_options(int argc, char **argv)
{
	if (argc == 1)
		g_info->debug_option = FALSE;
	else if (argc == 2 && !compare_size(argv[1], "-d"))
		g_info->debug_option = TRUE;
	else if (argc >= 3)
	{
		ft_printf("Too many arguments. Minisheh only ");
		ft_printf("supports one option (-d).\n");
		return (FAILURE);
	}
	else
	{
		ft_printf("Only one arguments is currently supported : ");
		ft_printf("'-d' to help debug.\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	if (ft_calloc((void **)&g_info, 1, sizeof(t_info)))
		exit(FAILURE);
	if (check_exec_options(argc, argv))
		exit(FAILURE);
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
	tgetent(NULL, getenv("TERM"));
	tcgetattr(STDOUT_FILENO, &g_info->termios_p);
	tcgetattr(STDOUT_FILENO, &g_info->saved_term);
	g_info->termios_p.c_lflag &= ~(ICANON | ECHO);
	g_info->termios_p.c_cc[VTIME] = 0;
	g_info->termios_p.c_cc[VMIN] = 1;
	g_info->cursor.col = tgetnum("co");
	g_info->cursor.lin = tgetnum("li");
	if (init_info(envp))
		exit(EXIT_FAILURE);
	init_termcap();
	exit(shell_loop());
}
