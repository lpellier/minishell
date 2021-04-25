/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:40:14 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/25 17:05:22 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** is used to reset all of the info after enter is pressed
*/

void	init_built_in(void)
{
	g_info->built_in[0] = ft_echo;
	g_info->built_in[1] = ft_echo_n;
	g_info->built_in[2] = ft_exit;
	g_info->built_in[3] = ft_pwd;
	g_info->built_in[4] = ft_export;
	g_info->built_in[5] = ft_unset;
	g_info->built_in[6] = ft_env;
	g_info->built_in[7] = ft_cd;
	g_info->built_in[8] = exec_binary;
	g_info->built_in[9] = nothing;
}

int	init_env(char **envp)
{
	int		i;
	char	**key_value;

	i = 0;
	if (!envp[i])
		return (FAILURE);
	key_value = ft_split(envp[i], '=');
	g_info->env_head = ft_create_elem(create_env_struct(ft_strdup(key_value[0]), \
		ft_strdup(key_value[1])));
	free_tab(&key_value);
	i++;
	while (envp[i])
	{
		key_value = ft_split(envp[i], '=');
		if (key_value && key_value[0] && key_value[1])
			ft_list_push_back(&g_info->env_head, \
				create_env_struct(ft_strdup(key_value[0]), \
				ft_strdup(key_value[1])));
		free_tab(&key_value);
		i++;
	}
	return (SUCCESS);
}

int	init_info(char **envp)
{
	t_env	*shlvl;
	
	init_env(envp);
	if (init_terminal())
		return (FAILURE);
	if (ft_calloc((void **)&g_info->line, 4096, sizeof(char)))
		return (FAILURE);
	init_built_in();
	g_info->echo_padding = 0;
	g_info->crashed = FALSE;
	g_info->cmd_status = 0;
	g_info->sig_status = 0;
	shlvl = get_env_custom("SHLVL");
	if (shlvl)
		shlvl->value = ft_itoa(ft_atoi(shlvl->value) + 1);
	ft_list_push_front(&g_info->env_head, create_env_struct(ft_strdup("?"), \
		ft_itoa(g_info->cmd_status)));
	reset_info();
	return (SUCCESS);
}

void	reset_info(void)
{
	t_env	*env;

	env = get_env_custom("PATH");
	free_tab(&g_info->dir_paths);
	if (g_info->dir_paths)
		free(g_info->dir_paths);
	if (env)
		g_info->dir_paths = ft_split(env->value, ':');
	else
		g_info->dir_paths = NULL;
	g_info->cur_in_history = 0;
	g_info->kill = FALSE;
	g_info->cursor.posy = 0;
	g_info->index_cmd = -1;
	g_info->bin_running = FALSE;
	free_blocks(g_info->block_head);
	g_info->block_head = ft_create_elem(create_block_struct(-1, -1));
	g_info->colon_nbr = 0;
	g_info->status = -1;
	ft_list_clear(g_info->cmd_head, free_cmd_struct);
	ft_bzero(g_info->cur_path, ft_strlen(g_info->cur_path));
}
