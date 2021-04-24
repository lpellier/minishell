/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:36:09 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/24 20:32:36 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// /*
// ** change directory, will need a find function in linked list
// ** to check for right bui and right input
// */

int	nothing_in_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	ft_cd(int index_cmd)
{
	t_cmd	*cmd;
	t_env	*old_pwd;
	t_env	*pwd;
	t_env	*cd_path;
	t_env	*home;
	char	cwd[PATH_MAX];
	char	*path;
	char	*tmp;
	char	*strjoin;

	path = NULL;
	cmd = ft_list_at(g_info->cmd_head, index_cmd)->data;
	home = get_env_custom("HOME");
	old_pwd = get_env_custom("OLDPWD");
	cd_path = get_env_custom("CDPATH");
	if (home && !cmd->option && (!cmd->input || !compare_size(cmd->input, "~")) && nothing_in_str(home->value))
		path = ft_strdup(home->value);
	else if (home && !cmd->option && (!cmd->input || !compare_size(cmd->input, "~")) && !nothing_in_str(home->value))
		path = ft_strdup(".");
	else if (old_pwd && !compare_size(cmd->input, "-"))
	{
		path = ft_strdup(old_pwd->value);
		ft_printf("%s\n", path);
	}
	else if (cmd->option)
	{
		ft_printf("minisheh: %s: %s: invalid option\n", cmd->cmd, cmd->option);
		return (FAILURE);
	}
	else
		path = ft_strdup(cmd->input);
	if (cd_path)
	{
		tmp = ft_strdup(path);
		secure_free(path);
		if (!compare_size(cd_path->value, "/"))
			path = ft_strjoin(cd_path->value, tmp);
		else
		{
			strjoin = ft_strjoin(cd_path->value, "/");
			path = ft_strjoin(strjoin, tmp);
			secure_free(strjoin);
		}
		secure_free(tmp);
	}
	if (multiple_args(path))
		ft_printf("minisheh: cd: too many arguments.\n");
	if (chdir(path))
		ft_printf("minisheh: cd: no such file or directory: %s\n", path);
	secure_free(path);
	pwd = get_env_custom("PWD");
	if (!pwd)
		return (FAILURE);
	modify_env("OLDPWD", pwd->value, 0);
	modify_env("PWD", getcwd(cwd, sizeof(cwd)), 0);
	return (SUCCESS);
}

/*
** this is used to count different arguments for binaries
** this WILL be tricky as we'll need to account for ""  and ''
** as a single argument
** and there might be backslashes canceling quotes ->
** it's going to be tough
*/

char	**count_args(t_cmd *cmd, int *count)
{
	char	**split;
	int		i;

	*count = 0;
	i = 0;
	if (cmd->input)
	{
		split = ft_split(cmd->input, ' ');
		while (split[i])
			i++;
		*count += i;
	}
	else
		split = NULL;
	if (cmd->cmd)
		*count += 1;
	if (cmd->option)
		*count += 1;
	return (split);
}

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

int	nothing(int index_cmd)
{
	(void)index_cmd;
	if (g_info->kill == FALSE)
		g_info->kill = TRUE;
	return (FAILURE);
}
