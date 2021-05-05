/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:36:09 by lpellier          #+#    #+#             */
/*   Updated: 2021/05/05 16:44:50 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	else if (!home && (!cmd->args[arg_index] || \
		!arg_is_empty(cmd, arg_index)))
	{
		print_error(NULL, "cd", "HOME not set", 1);
		return (NULL);
	}
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

/*
** this is used to count different arguments for binaries
** this WILL be tricky as we'll need to account for ""  and ''
** as a single argument
** and there might be backslashes canceling quotes ->
** it's going to be tough
*/

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
