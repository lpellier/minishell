/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:48:26 by lpellier          #+#    #+#             */
/*   Updated: 2021/05/12 13:05:45 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	save_std(&info->saved_stdin, &info->saved_stdout);
	exit(shell_loop(info));
}
