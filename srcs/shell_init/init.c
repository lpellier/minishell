/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:40:14 by lpellier          #+#    #+#             */
/*   Updated: 2021/05/20 12:37:19 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** is used to reset all of the info after enter is pressed
*/

void	init_built_in(t_info *info)
{
	info->built_in[0] = ft_echo;
	info->built_in[1] = ft_echo_n;
	info->built_in[2] = ft_exit;
	info->built_in[3] = ft_pwd;
	info->built_in[4] = ft_export;
	info->built_in[5] = ft_unset;
	info->built_in[6] = ft_env;
	info->built_in[7] = ft_cd;
	info->built_in[8] = exec_binary;
}

int	init_env(t_info *info, char **envp)
{
	int		i;
	char	**key_value;

	i = 0;
	if (!envp[i])
		return (FAILURE);
	key_value = ft_split(envp[i], '=');
	info->env_head->next = ft_create_elem(create_env_struct(\
		ft_strdup(key_value[0]), ft_strdup(key_value[1])));
	free_tab(&key_value);
	i++;
	while (envp[i])
	{
		key_value = ft_split(envp[i], '=');
		if (key_value && key_value[0] && key_value[1])
			ft_list_push_back(&info->env_head->next, \
				create_env_struct(ft_strdup(key_value[0]), \
				ft_strdup(key_value[1])));
		free_tab(&key_value);
		i++;
	}
	return (SUCCESS);
}

void	set_lint(t_info *info, int *lint)
{
	int		i;

	i = 0;
	info->lint_index = 0;
	info->line_index = 0;
	while (i < LINE_MAX)
	{
		lint[i] = -1;
		i++;
	}
}

int	init_terminal(t_info *info)
{
	t_env	*term;

	term = get_env_custom(info, "TERM");
	if (!term || !term->value)
		return (print_error(NULL, \
			NULL, "TERM environment variable not set.\nBye.\n", 1));
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
	tgetent(NULL, term->value);
	tcgetattr(STDOUT_FILENO, &info->termios_p);
	tcgetattr(STDOUT_FILENO, &info->saved_term);
	info->termios_p.c_lflag &= ~(ICANON | ECHO);
	info->termios_p.c_cc[VTIME] = 0;
	info->termios_p.c_cc[VMIN] = 1;
	info->terminfo.col = tgetnum("co");
	info->terminfo.lin = tgetnum("li");
	init_termcap(info);
	return (SUCCESS);
}

void	reset_dir_paths(t_info *info)
{
	t_env	*env;

	env = get_env_custom(info, "PATH");
	free_tab(&info->dir_paths);
	if (info->dir_paths)
		free(info->dir_paths);
	if (env)
		info->dir_paths = ft_split(env->value, ':');
	else
		info->dir_paths = NULL;
}
