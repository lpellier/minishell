/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:21:27 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/21 12:38:38 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_binary_check(t_cmd *cmd, char **argv, char **split)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (cmd->option)
	{
		argv[j] = ft_strdup(cmd->option);
		j++;
	}
	if (split && split[0])
	{
		while (split[i])
		{
			argv[j] = ft_strdup(split[i]);
			i++;
			j++;
		}
	}
	else if (cmd->input)
	{
		argv[j] = ft_strdup(cmd->input);
		j++;
	}
	argv[j] = NULL;
}

int	exec_binary(int index_cmd)
{
	t_cmd	*cmd;
	int		count;
	char	**argv;
	char	**split;
	char	**env;

	cmd = ft_list_at(g_info->cmd_head, index_cmd)->data;
	env = list_to_tab(g_info->env_head);
	split = count_args(cmd, &count);
	if (ft_calloc((void **)&argv, count + 1, sizeof(char *)))
		return (FAILURE);
	argv[0] = ft_strdup(cmd->cmd);
	exec_binary_check(cmd, argv, split);
	if (execve(cmd->path, argv, env) == -1)
		return (FAILURE);
	free_tab(&split);
	free_tab(&argv);
	free_tab(&env);
	return (SUCCESS);
}

int	find_binary(t_cmd *cmd)
{
	char	*path;
	char	*actu_cmd;
	int		i;

	i = 0;
	actu_cmd = NULL;
	path = get_folder_path(cmd->cmd, &actu_cmd);
	if (!directories(path, actu_cmd))
	{
		cmd->path = ft_strdup(cmd->cmd);
		return (SUCCESS);
	}
	if (!g_info->dir_paths)
		return (FAILURE);
	while (g_info->dir_paths[i])
	{
		if (!directories(g_info->dir_paths[i], cmd->cmd))
		{
			cmd->path = ft_strjoin(ft_strjoin(g_info->dir_paths[i], "/"), \
				cmd->cmd);
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}
