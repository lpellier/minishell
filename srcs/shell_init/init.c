/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:40:14 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/09 12:48:23 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** is used to reset all of the info after enter is pressed
*/

void		init_built_in(void)
{
	g_info.built_in[0] = ft_echo;
	g_info.built_in[1] = ft_echo_n;
	g_info.built_in[2] = ft_exit;
	g_info.built_in[3] = ft_pwd;
	g_info.built_in[4] = ft_export;
	g_info.built_in[5] = ft_unset;
	g_info.built_in[6] = ft_env;
	g_info.built_in[7] = ft_cd;
	g_info.built_in[8] = exec_binary;
}

int			init_env(char **envp)
{
	int		i;
	char	**key_value;

	i = 0;
	if (!envp[i])
		return (FAILURE);
	key_value = ft_split(envp[i], '=');
	g_info.env_head = ft_create_elem(create_env_struct(ft_strdup(key_value[0]), ft_strdup(key_value[1])));
	free_tab(&key_value);
	i++;
	while (envp[i])
	{
		if ((key_value = ft_split(envp[i], '=')) && key_value[0] && key_value[1])
			ft_list_push_back(&g_info.env_head,
				create_env_struct(ft_strdup(key_value[0]), ft_strdup(key_value[1])));
		free_tab(&key_value);
		i++;
	}
	return (SUCCESS);
}

void		init_info(char **envp)
{
	init_built_in();
	g_info.echo_padding = 0;
	g_info.crashed = FALSE;
	g_info.output = NULL;
	g_info.cmd_status = 0;
	init_env(envp);
	ft_list_push_front(&g_info.env_head, create_env_struct(ft_strdup("?"),
		ft_itoa(g_info.cmd_status)));
	g_info.dir_paths = ft_split(getenv("PATH"), ':');
	reset_info();
}

void reset_info()
{
	g_info.cur_in_history = 0;
	g_info.kill = FALSE;
	g_info.bin_running = FALSE;
	g_info.block_head = ft_create_elem(create_block_struct(-1, -1));
}
