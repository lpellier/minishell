/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_things.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:44:07 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/12 14:09:08 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// /*
// ** change directory, will need a find function in linked list
// ** to check for right bui and right input
// */

int	check_for_cdpath(t_info *info, char **path)
{
	t_env	*cdpath;
	char	*tmp;
	char	*strjoin;

	cdpath = get_env_custom(info, "CDPATH");
	if (cdpath)
	{
		tmp = ft_strdup(*path);
		secure_free(*path);
		if (!compare_size(cdpath->value, "/"))
			*path = ft_strjoin(cdpath->value, tmp);
		else
		{
			strjoin = ft_strjoin(cdpath->value, "/");
			*path = ft_strjoin(strjoin, tmp);
			secure_free(strjoin);
		}
		secure_free(tmp);
		return (SUCCESS);
	}
	return (FAILURE);
}

int	just_secure_free(char *path)
{
	secure_free(path);
	return (SUCCESS);
}

int	chdir_n_free(t_info *info, char *path)
{
	check_for_cdpath(info, &path);
	if (!info->piped && chdir(path))
	{
		print_error("cd", path, "no such file or directory", 1);
		secure_free(path);
		return (FAILURE);
	}
	secure_free(path);
	update_pwd(info);
	return (SUCCESS);
}

int	ft_cd(t_info *info, t_cmd *cmd)
{
	char	*path;
	int		arg_index;

	arg_index = cmd->arg_index + 1;
	if (!arg_is_option(cmd->args[arg_index]) && \
		compare_size(cmd->args[arg_index], "-"))
		return (print_error(cmd->args[arg_index - 1], \
			cmd->args[arg_index], "invalid option", 1));
	if (cmd->args && cmd->args[arg_index] && \
		cmd->args[arg_index + 1] && arg_index + 1 < cmd->limit_index)
		return (print_error(NULL, "cd", "too many arguments", 1));
	path = define_path(info, cmd, arg_index);
	if (!path)
		return (FAILURE);
	else if (!compare_size(path, ""))
		return (just_secure_free(path));
	return (chdir_n_free(info, path));
}
