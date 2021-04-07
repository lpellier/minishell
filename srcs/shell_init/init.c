/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:40:14 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/07 15:22:48 by tefroiss         ###   ########.fr       */
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

/*
** mallocs and creates cmd struct, returns pointer on struct
*/

t_cmd		*create_cmd_struct(void)
{
	t_cmd	*cmd;

	if (ft_calloc((void **)&cmd, 1, sizeof(t_cmd)))
		return (NULL);
	cmd->bui = 9;
	cmd->cmd = NULL;
	cmd->input = NULL;
	cmd->option = NULL;
	cmd->path = NULL;
	return (cmd);
}

/*
** same as above for env struct
*/

t_env		*create_env_struct(char *key, char *value)
{
	t_env	*env;

	if (ft_calloc((void **)&env, 1, sizeof(t_env)))
		return (NULL);
	env->key = key;
	env->value = value;
	return (env);
}

t_history *create_history_struct()
{
    t_history *history;

    if (ft_calloc((void **)&history, 1, sizeof(t_history)))
		return (NULL);
	if (ft_calloc((void **)&history->line, LINE_MAX, sizeof(char)))
		return (NULL);
    return (history);
}

void		init_info(char **envp)
{
	init_built_in();
	g_info.crashed = FALSE;
	g_info.output = NULL;
	g_info.cmd_status = 0;
	init_env(envp);
	//info.dir_paths = NULL;
	ft_list_push_front(&g_info.env_head, create_env_struct(ft_strdup("?"),
		ft_itoa(g_info.cmd_status)));
	g_info.dir_paths = ft_split(getenv("PATH"), ':');
	// info.dir_paths = ft_split(((t_env *)ft_list_find(info.env_head, create_env_struct("PATH", NULL), cmp_env)->data)->value, ":");
	reset_info();
}

void reset_info()
{
	g_info.cur_in_history = 0;
	// info.nb_colon = 0;
	// info.nb_l_redir = 0;
	// info.nb_pipe = 0;
	// info.nb_r_redir = 0;
	// info.nb_rd_redir = 0;
}
