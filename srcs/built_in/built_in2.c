/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:36:09 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/21 15:22:25 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// /*
// ** change directory, will need a find function in linked list
// ** to check for right bui and right input
// */

int	ft_cd(int index_cmd)
{
	t_cmd	*cmd;
	t_env	*pwd;
	char	cwd[PATH_MAX];
	char	*path;

	path = NULL;
	cmd = ft_list_at(g_info->cmd_head, index_cmd)->data;
	if (cmd->option)
	{
		ft_printf("minisheh: %s: %s: invalid option\n", cmd->cmd, cmd->option);
		return (FAILURE);
	}
	if (!cmd->input)
		path = ft_strdup(get_env_custom("HOME")->value);
	else
		path = ft_strdup(cmd->input);
	if (chdir(path))
		ft_printf("Couldn't access folder, check directory listing\n");
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

char	*get_folder_path(char *cmd, char **actu_cmd)
{
	char	*ret;
	int		i;

	i = ft_strlen(cmd);
	ret = NULL;
	if (i > 0)
		i--;
	while (cmd && i > 0 && cmd[i])
	{
		if (cmd[i] == '/')
			break ;
		i--;
	}
	if (i > 0)
		ret = ft_strndup(cmd, i - 1);
	*actu_cmd = ft_substr(cmd, i, ft_strlen(cmd));
	return (ret);
}

int	nothing(int index_cmd)
{
	(void)index_cmd;
	if (g_info->kill == FALSE)
		g_info->kill = TRUE;
	return (FAILURE);
}
