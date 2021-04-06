/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:40:14 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/04 13:37:47 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** is used to reset all of the info after enter is pressed
*/

void		init_built_in(void)
{
	info.built_in[0] = ft_echo;
	info.built_in[1] = ft_echo_n;
	info.built_in[2] = ft_exit;
	info.built_in[3] = ft_pwd;
	info.built_in[4] = ft_export;
	info.built_in[5] = ft_unset;
	info.built_in[6] = ft_env;
	info.built_in[7] = ft_cd;
	info.built_in[8] = exec_binary;
}

int			init_env(char **envp)
{
	int		i;
	char	**key_value;

	i = 0;
	if (!envp[i])
		return (FAILURE);
	key_value = ft_split(envp[i], '=');
	info.env_head = ft_create_elem(create_env_struct(ft_strdup(key_value[0]), ft_strdup(key_value[1])));
	free_tab(&key_value);
	i++;
	while (envp[i])
	{
		if ((key_value = ft_split(envp[i], '=')) && key_value[0] && key_value[1])
			ft_list_push_back(&info.env_head,
				create_env_struct(ft_strdup(key_value[0]), ft_strdup(key_value[1])));
		free_tab(&key_value);
		i++;
	}
	return (SUCCESS);
}

void		init_info(char **envp)
{
	init_built_in();
	info.crashed = FALSE;
	info.output = NULL;
	info.echo_padding = 0;
	info.cmd_status = 0;
	init_env(envp);
	ft_list_push_front(&info.env_head, create_env_struct(ft_strdup("?"),
		ft_itoa(info.cmd_status)));
	info.dir_paths = ft_split(get_env_custom("PATH")->value, ':');
	reset_info();
}

void reset_info()
{
	info.cur_in_history = 0;
}
