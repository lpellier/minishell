/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:03:40 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/30 15:56:49 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_sigint(int sig)
{
	char	*cur_dir;
	char	*strjoin;
	char	*prompt;

	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	g_signal->kill = TRUE;
	if (!g_signal->bin_running)
	{
		cur_dir = get_cur_dir();
		if (!(cur_dir))
			cur_dir = ft_strdup("/");
		strjoin = ft_strjoin("\033[34m~ ", cur_dir);
		prompt = ft_strjoin(strjoin, " > \x1b[0m");
		secure_free(strjoin);
		ft_printf("%s", prompt);
		secure_free(prompt);
	}
}

void	ft_sigquit(int sig)
{
	(void)sig;
	write(2, "\b\b  ", 4);
	write(2, "\b\b", 2);
	// update_cmd_status(info, 131);
}
