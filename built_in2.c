/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:36:09 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/11 11:22:30 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**destroys a environment variable from memory
*/

int			ft_unset(t_info *info, int index_cmd)
{
	t_cmd	*cmd;

	cmd = ft_list_at(info->cmd_head, index_cmd)->data;
	if (!info->env_head || !info->env_head->next || !info->env_head->next->next)
		return (FAILURE);
	ft_list_remove_if(&info->env_head->next->next,
		create_env_struct(cmd->input, NULL), cmp_env, free_env_struct);
	return (SUCCESS);
}

/*
** outputs all environment variables
*/

int			ft_env(t_info *info, int index_cmd)
{
	(void)index_cmd;
	if (!info->env_head || !info->env_head->next || !info->env_head->next->next)
		return (FAILURE);
	ft_list_foreach(info->env_head->next->next, print_env_struct);
	return (SUCCESS);
}

/*
** change directory, will need a find function in linked list
** to check for right bui and right input
*/

int			ft_cd(t_info *info, int index_cmd)
{
	t_cmd	*cmd;
	char	cwd[PATH_MAX];
	char	*user;

	cmd = ft_list_at(info->cmd_head, index_cmd)->data;
	user = ft_strjoin("/Users/", ((t_env *)ft_list_find(info->env_head,
		create_env_struct("USER", NULL), cmp_env)->data)->value);
	if (!cmd->input)
	{
		if (chdir(user))
			ft_printf("Couldn't access folder, check directory listing\n");
		free(user);
	}
	else if (cmd->input[0] == '/')
	{
		if (chdir(cmd->input))
			ft_printf("Couldn't access folder, check directory listing\n");
	}
	else if (getcwd(cwd, sizeof(cwd)))
	{
		if (chdir(ft_strjoin(ft_strjoin(cwd, "/"), cmd->input)))
			ft_printf("Couldn't access folder, check directory listing\n");
	}
	else
		ft_printf("Error\n");
	return (SUCCESS);
}

/*
** this is used to count different arguments for binaries
** this WILL be tricky as we'll need to account for ""  and ''
** as a single argument
** and there might be backspaces canceling quotes -> it's going to be tough
*/

char		**count_args(t_cmd *cmd, int *count)
{
	char	**split;
	int		i;

	*count = 0;
	i = 0;
	if (cmd->input)
	{
		split = ft_split(cmd->input, " ");
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

char		**list_to_tab(t_list *begin_list)
{
	t_list	*next;
	t_env	*env;
	char	**ret;
	int		i;

	i = 0;
	next = begin_list->next;
	if (!(ret = (char **)malloc(sizeof(char *) * (ft_list_size(next) + 1))))
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

int			exec_binary(t_info *info, int index_cmd)
{
	t_cmd	*cmd;
	int		count;
	int		i;
	int		j;
	char	**argv;
	char	**split;
	char	**env;

	cmd = ft_list_at(info->cmd_head, index_cmd)->data;
	env = list_to_tab(info->env_head);
	split = count_args(cmd, &count);
	if (!(argv = (char **)malloc(sizeof(char *) * count + 1)))
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
	free_tab(split);
	free_tab(argv);
	free_tab(env);
	return (SUCCESS);
}

int			compare_size(char *s1, char *s2)
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

int			find_binary(t_info *info, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (info->dir_paths[i])
	{
		if (!directories(info->dir_paths[i], cmd->cmd))
		{
			cmd->path = ft_strjoin(ft_strjoin(info->dir_paths[i], "/"),
				cmd->cmd);
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}

void		compare_cmd(t_info *info, t_cmd *cmd)
{
	if (!cmd->cmd)
		cmd->bui = NONEXISTENT;
	else if (!compare_size(cmd->cmd, "echo") && cmd->option \
	&& !compare_size(cmd->option, "-n"))
		cmd->bui = ECHO_N;
	else if (!compare_size(cmd->cmd, "echo"))
		cmd->bui = ECHO;
	else if (!compare_size(cmd->cmd, "exit"))
		cmd->bui = EXIT;
	else if (!compare_size(cmd->cmd, "pwd"))
		cmd->bui = PWD;
	else if (!compare_size(cmd->cmd, "export"))
		cmd->bui = EXPORT;
	else if (!compare_size(cmd->cmd, "unset"))
		cmd->bui = UNSET;
	else if (!compare_size(cmd->cmd, "env"))
		cmd->bui = ENV;
	else if (!compare_size(cmd->cmd, "cd"))
		cmd->bui = CD;
	else if (!find_binary(info, cmd))
		cmd->bui = BINARY;
	else
		cmd->bui = NONEXISTENT;
}
