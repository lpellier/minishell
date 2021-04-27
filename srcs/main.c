/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:48:26 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/27 11:52:17 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	print_error_option(t_cmd *cmd)
// {
// 	(void)cmd;
// 	// ft_printf("minisheh: %s: %s: invalid option\n", cmd->cmd, cmd->option);
// 	return (FAILURE);
// }

int	print_error(char *error)
{
	ft_printf("%s\n", error);
	return (FAILURE);
}

int	delete_empty_history(void *data, void *data_ref)
{
	t_history	*ptr;

	(void)data_ref;
	ptr = (t_history *)data;
	if (!ptr || !ptr->line || (ptr->line && !ptr->line[0]))
		return (SUCCESS);
	return (FAILURE);
}

void	update_cmd_status(t_info *info, int new_code)
{
	t_env	*data;

	data = (t_env *)info->env_head->data;
	secure_free(data->value);
	data->value = ft_itoa(new_code);
}

void	print_prompt(t_info *info)
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
	info->terminfo.prompt_len = ft_strlen(cur_dir) + 5;
	info->cursor.posx = info->terminfo.prompt_len + info->terminfo.echo_padding;
	info->cursor.posy = 0;
	secure_free(cur_dir);
}

/*
** sole reason of first var is to create head of history linked list in read_line
*/

int	shell_loop(t_info *info)
{
	int		first;

	first = TRUE;
	ft_putstr_fd("\033[31mWelcome to Minisheh\n\x1b[0m", STDERR_FILENO);
	while (!info->crashed)
	{
		print_prompt(info);
		process_line(info, first);
		first = FALSE;
		reset_info(info);
		ft_list_remove_if(&info->history_head, NULL, delete_empty_history, \
		free_history_struct);
	}
	free_tab(&info->dir_paths);
	secure_free(info->line);
	ft_list_clear(info->env_head, free_env_struct);
	ft_list_clear(info->history_head, free_history_struct);
	secure_free(info);
	return (SUCCESS);
}

int	check_exec_options(t_info *info, int argc, char **argv)
{
	if (argc == 1)
		info->debug_option = FALSE;
	else if (argc == 2 && !compare_size(argv[1], "-d"))
		info->debug_option = TRUE;
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
	t_info		*info;

	if (ft_calloc((void **)&g_signal, 1, sizeof(t_signal)))
		exit(FAILURE);
	g_signal->kill = FALSE;
	g_signal->bin_running = FALSE;
	if (ft_calloc((void **)&info, 1, sizeof(t_info)))
		exit(FAILURE);
	if (check_exec_options(info, argc, argv))
	{
		secure_free(info);
		exit(FAILURE);
	}
	if (init_info(info, envp))
	{
		secure_free(info);
		exit(FAILURE);
	}
	exit(shell_loop(info));
}
