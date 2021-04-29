/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_std.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:24:27 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/29 17:18:02 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cinset(const char c, const char *set)
{
	int	i;

	if (set != NULL)
	{
		i = 0;
		while (set[i])
		{
			if (c == set[i])
				return (SUCCESS);
			i++;
		}
		return (FAILURE);
	}
	return (OTHER);
}

int	open_file(t_cmd *cmd, int start, int separator)
{
	int		arg_index;
	int		file_fd;

	file_fd = -1;
	arg_index = sep_in_args(cmd, start) + 1;
	if (separator == R_RIGHT)
		file_fd = open(cmd->args[arg_index], O_WRONLY | O_TRUNC | O_CREAT, 00644);
	else if (separator == R_RIGHTD)
		file_fd = open(cmd->args[arg_index], O_WRONLY | O_APPEND | O_CREAT, 00644);
	else if (separator == R_LEFT)
	{
		file_fd = open(cmd->args[arg_index], O_RDONLY, 00644);
		if (file_fd == -1)
			print_error(NULL, cmd->args[arg_index], \
				"no such file or directory");
	}
	return (file_fd);
}
