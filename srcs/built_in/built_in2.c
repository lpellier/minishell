/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:36:09 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/08 17:15:43 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** change directory, will need a find function in linked list
** to check for right bui and right input
*/

void	secure_free(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

int	ft_cd(int index_cmd)
{
	t_cmd	*cmd;
	char	cwd[PATH_MAX];
	char	*path;

	path = NULL;
	cmd = ft_list_at(g_info.cmd_head, index_cmd)->data;
	if (cmd->option)
	{
		ft_printf("minisheh: %s: %s: invalid option\n", cmd->cmd, cmd->option);
		return (FAILURE);
	}
	if (!cmd->input)
		path = ft_strdup(get_env_custom("HOME")->value);
	else if (cmd->input[0] == '/' && compare_size(cmd->input, "/"))
		path = ft_strdup(cmd->input);
	else if (getcwd(cwd, sizeof(cwd)))
		path = ft_strjoin(ft_strjoin(cwd, "/"), cmd->input);
	else
		ft_printf("Error\n");
	if (chdir(path))
		ft_printf("Couldn't access folder, check directory listing\n");
	modify_env("OLDPWD", get_env_custom("PWD")->value, 0);
	modify_env("PWD", getcwd(cwd, sizeof(cwd)), 0);
	secure_free(path);
	return (SUCCESS);
}

char	**list_to_tab(t_list *begin_list)
{
	t_list	*next;
	t_env	*env;
	char	**ret;
	int		i;

	i = 0;
	next = begin_list->next;
	if (ft_calloc((void **)&ret, ft_list_size(next) + 1, sizeof(char *)))
		return (NULL);
	while (next)
	{
		env = (t_env *)next->data;
		ret[i] = ft_strjoin(ft_strjoin(env->key, "="), env->value);
		next = next->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

/*
** this is where the complex split depending on quotes
** and backslashes will happen
** for now it's only split by spaces for simplicity
*/

int	exec_binary(int index_cmd)
{
	t_cmd	*cmd;
	int		count;
	int		i;
	int		j;
	char	**argv;
	char	**split;
	char	**env;

	cmd = ft_list_at(g_info.cmd_head, index_cmd)->data;
	env = list_to_tab(g_info.env_head);
	split = count_args(cmd, &count);
	if (ft_calloc((void **)&argv, count + 1, sizeof(char *)))
		return (FAILURE);
	argv[0] = ft_strdup(cmd->cmd);
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
	if (execve(cmd->path, argv, env) == -1)
		return (FAILURE);
	free_tab(&split);
	free_tab(&argv);
	free_tab(&env);
	return (SUCCESS);
}

int	compare_size(char *s1, char *s2)
{
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!ft_strncmp(s1, s2, len1) && len1 == len2)
		return (SUCCESS);
	else
		return (FAILURE);
}

int	find_binary(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (!g_info.dir_paths)
		return (FAILURE);
	while (g_info.dir_paths[i])
	{
		if (!directories(g_info.dir_paths[i], cmd->cmd))
		{
			cmd->path = ft_strjoin(ft_strjoin(g_info.dir_paths[i], "/"), \
				cmd->cmd);
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}
