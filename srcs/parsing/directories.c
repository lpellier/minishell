/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:25:58 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/07 17:26:38 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** This function will be used to check for executables
** in directories addressed in $PATH
*/

int			directories(char *path, char *cmd)
{
	DIR				*d;
	struct dirent	*dir;

	d = opendir(path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
			if (!compare_size(cmd, dir->d_name))
				return (SUCCESS);
		closedir(d);
	}
	return (FAILURE);
}

char		*get_cur_dir()
{
	int		i;
	char	**split;
	char	*res;

	i = 0;
	getcwd(g_info.cur_path, sizeof(g_info.cur_path));
	split = ft_split(g_info.cur_path, '/');
	while (split[i])
		i++;
	if (i == 0)
		res = NULL;
	else
		res = ft_strdup(split[i - 1]);
	free_tab(&split);
	return (res);
}
