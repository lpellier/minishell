/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:25:58 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/26 23:38:21 by lpellier         ###   ########.fr       */
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

	if (!path)
		return (FAILURE);
	d = opendir(path);
	if (d)
	{
		dir = readdir(d);
		while (dir != NULL)
		{
			if (!compare_size(cmd, dir->d_name))
			{
				closedir(d);
				return (SUCCESS);
			}
			dir = readdir(d);
		}
		closedir(d);
	}
	return (FAILURE);
}

char	*get_cur_dir(void)
{
	int		i;
	char	cwd[PATH_MAX];
	char	**split;
	char	*res;

	i = 0;
	getcwd(cwd, sizeof(cwd));
	if (!compare_size(cwd, "/"))
	{
		res = ft_strdup(cwd);
		return (res);
	}
	split = ft_split(cwd, '/');
	while (split[i])
		i++;
	if (i == 0)
		res = NULL;
	else
		res = ft_strdup(split[i - 1]);
	free_tab(&split);
	return (res);
}
