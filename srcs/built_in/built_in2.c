/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:36:09 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/30 17:48:18 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// /*
// ** change directory, will need a find function in linked list
// ** to check for right bui and right input
// */

void	check_for_cdpath(t_info *info, char *path)
{
	t_env	*cdpath;
	char	*tmp;
	char	*strjoin;

	cdpath = get_env_custom(info, "CDPATH");
	if (cdpath)
	{
		tmp = ft_strdup(path);
		secure_free(path);
		if (!compare_size(cdpath->value, "/"))
			path = ft_strjoin(cdpath->value, tmp);
		else
		{
			strjoin = ft_strjoin(cdpath->value, "/");
			path = ft_strjoin(strjoin, tmp);
			secure_free(strjoin);
		}
		secure_free(tmp);
	}
}

void	update_pwd(t_info *info)
{
	t_env	*pwd;
	char	cwd[PATH_MAX];
	
	pwd = get_env_custom(info, "PWD");
	if (!pwd)
		return ;
	modify_env(info, "OLDPWD", pwd->value, 0);
	modify_env(info, "PWD", getcwd(cwd, sizeof(cwd)), 0);
}

char	*define_path(t_info *info, t_cmd *cmd, int arg_index)
{
	t_env	*oldpwd;
	t_env	*home;
	char	*path;

	path = NULL;
	home = get_env_custom(info, "HOME");
	oldpwd = get_env_custom(info, "OLDPWD");
	if (home && home->value && !cmd->args[arg_index])
		path = ft_strdup(home->value);
	else if ((!home && !cmd->args[arg_index]) || (home && !home->value))
		return (NULL);
	else if (oldpwd && oldpwd->value && \
		!compare_size(cmd->args[arg_index], "-"))
	{
		path = ft_strdup(oldpwd->value);
		ft_putstr_fd(path, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else
		path = ft_strdup(cmd->args[arg_index]);
	return (path);
}

int	ft_cd(t_info *info, t_cmd *cmd)
{
	char	*path;
	int		arg_index;

	arg_index = cmd->arg_index + 1;
	if (!arg_is_option(cmd->args[arg_index]) && compare_size(cmd->args[arg_index], "-"))	
		return (print_error(cmd->args[arg_index - 1], \
			cmd->args[arg_index], "invalid option", 1));
	if (cmd->args && cmd->args[arg_index] && \
		cmd->args[arg_index + 1])
		return (print_error(NULL, "cd", "too many arguments", 1));
	path = define_path(info, cmd, arg_index);
	if (!path || (cmd->lint[arg_index] && cmd->lint[arg_index][0] == _EMPTY_CHAR))
		return (print_error(NULL, "cd", "HOME not set", 1));
	check_for_cdpath(info, path);
	if (chdir(path))
		return (print_error("cd", path, "no such file or directory", 1));
	secure_free(path);
	update_pwd(info);
	return (SUCCESS);
}

/*
** this is used to count different arguments for binaries
** this WILL be tricky as we'll need to account for ""  and ''
** as a single argument
** and there might be backslashes canceling quotes ->
** it's going to be tough
*/

// char	**count_args(t_cmd *cmd, int *count)
// {
// 	char	**split;
// 	int		i;

// 	*count = 0;
// 	i = 0;
// 	if (cmd->input)
// 	{
// 		split = ft_split(cmd->input, ' ');
// 		while (split[i])
// 			i++;
// 		*count += i;
// 	}
// 	else
// 		split = NULL;
// 	if (cmd->cmd)
// 		*count += 1;
// 	if (cmd->option)
// 		*count += 1;
// 	return (split);
// }

char	**list_to_tab(t_list *begin_list)
{
	t_list	*next;
	t_env	*env;
	char	**ret;
	char	*strjoin;
	int		i;

	i = 0;
	next = begin_list->next;
	if (ft_calloc((void **)&ret, ft_list_size(next) + 1, sizeof(char *)))
		return (NULL);
	while (next)
	{
		env = (t_env *)next->data;
		strjoin = ft_strjoin(env->key, "=");
		ret[i] = ft_strjoin(strjoin, env->value);
		secure_free(strjoin);
		next = next->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

char	*get_actual_cmd(char *cmd, char **path)
{
	char	*ret;
	char	**split;
	int		i;
	int		path_len;

	i = 0;
	split = ft_split(cmd, '/');
	if (!split)
		return (NULL);
	while (split[i])
		i++;
	if (i > 0)
		i--;
	ret = ft_strdup(split[i]);
	path_len = ft_strlen(cmd) - ft_strlen(ret) - 1;
	if (path_len > 0)
		*path = ft_strndup(cmd, path_len);
	else
		*path = NULL;
	free_tab(&split);
	return (ret);
}

