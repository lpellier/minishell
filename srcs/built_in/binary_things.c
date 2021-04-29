/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:21:27 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/29 12:54:18 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	binary_process(t_info *info, t_cmd *cmd)
{
	char	**argv;
	char	**env;
	int		arg_index;
	int i;

	arg_index = cmd->arg_index;
	if (ft_calloc((void **)&argv, cmd->limit_index - arg_index + 1, sizeof(char *)))
		return (FAILURE);
	env = list_to_tab(info->env_head);
	i = 0;
	while (cmd->args && cmd->args[arg_index] && arg_index < cmd->limit_index)
	{
		argv[i] = ft_strdup(cmd->args[arg_index]);
		i++;
		arg_index++;
	}
	argv[i] = NULL;
	if (execve(cmd->path, argv, env) == -1)
	{
		free_tab(&argv);
		free_tab(&env);
		return (errno);
	}
	free_tab(&argv);
	free_tab(&env);
	return (SUCCESS);
}

int	exec_binary(t_info *info, t_cmd *cmd)
{
	int		status;
	pid_t	cpid;
	
	g_signal->bin_running = TRUE;
	restore_term(info);
	cpid = fork();
	if (cpid == -1)
		return (FAILURE);
	else if (cpid == 0)
		_exit(binary_process(info, cmd));
	else
	{
		waitpid(cpid, &status, 0);
		g_signal->bin_running = FALSE;
		init_termcap(info);
		update_cmd_status(info, status % 255);
		// interpret_errors(info);
		return (status);
	}
}

int	check_in_path(t_info *info, t_cmd *cmd, int arg_index)
{
	char	*strjoin;
	int		i;

	if (!info->dir_paths)
		return (FAILURE);
	i = 0;
	while (info->dir_paths[i])
	{
		if (!directories(info->dir_paths[i], cmd->args[arg_index]))
		{
			strjoin = ft_strjoin(info->dir_paths[i], "/");
			cmd->path = ft_strjoin(strjoin, cmd->args[arg_index]);
			secure_free(strjoin);
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}

int	find_binary(t_info *info, t_cmd *cmd)
{
	char	*actu_cmd;
	char	*path;
	int		arg_index;

	arg_index = cmd->arg_index;
	if (!compare_size(cmd->args[arg_index], ".") || \
		!compare_size(cmd->args[arg_index], ".."))
		return (FAILURE);
	actu_cmd = get_actual_cmd(cmd->args[arg_index], &path);
	if (!directories(path, actu_cmd))
	{
		cmd->path = ft_strdup(cmd->args[arg_index]);
		secure_free(actu_cmd);
		secure_free(path);
		return (SUCCESS);
	}
	secure_free(actu_cmd);
	secure_free(path);
	return (check_in_path(info, cmd, arg_index));
}
