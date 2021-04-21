/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:25:58 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/21 15:04:43 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** This function will be used to check for executables
** in directories addressed in $PATH
*/

int	directories(char *path, char *cmd)
{
	DIR				*d;
	struct dirent	*dir;

	d = opendir(path);
	if (d)
	{
		dir = readdir(d);
		while (dir != NULL)
		{
			if (!compare_size(cmd, dir->d_name))
				return (SUCCESS);
			dir = readdir(d);
		}
		closedir(d);
	}
	return (FAILURE);
}

char	*get_cur_dir(void)
{
	int		i;
	char	**split;
	char	*res;

	i = 0;
	getcwd(g_info->cur_path, sizeof(g_info->cur_path));
	if (!compare_size(g_info->cur_path, "/"))
	{
		res = ft_strdup(g_info->cur_path);
		return (res);
	}
	split = ft_split(g_info->cur_path, '/');
	while (split[i])
		i++;
	if (i == 0)
		res = NULL;
	else
		res = ft_strdup(split[i - 1]);
	free_tab(&split);
	return (res);
}
