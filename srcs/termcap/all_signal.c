/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:03:40 by lpellier          #+#    #+#             */
/*   Updated: 2021/05/11 18:05:39 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_sigint(int sig)
{
	char	*cur_dir;
	char	*strjoin;
	char	*prompt;

	(void)sig;
	if (!g_signal->bin_running)
		ft_putstr_fd("^C", STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	g_signal->kill = 130;
	if (!g_signal->bin_running)
	{
		cur_dir = get_cur_dir();
		if (!(cur_dir))
			cur_dir = ft_strdup("/");
		strjoin = ft_strjoin("\033[34m~ ", cur_dir);
		secure_free(cur_dir);
		prompt = ft_strjoin(strjoin, " > \x1b[0m");
		secure_free(strjoin);
		ft_printf("%s", prompt);
		secure_free(prompt);
	}
}

void	ft_sigquit(int sig)
{
	(void)sig;
	g_signal->kill = 131;
	if (g_signal->bin_running)
	{
		write(2, "\b\b  ", 4);
		write(2, "\b\b", 2);
		ft_printf("^\\Quit: 3\n");
	}
}
