/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_std.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:24:27 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/19 11:32:00 by lpellier         ###   ########.fr       */
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

int	arg_is_dollared(t_cmd *cmd, int index)
{
	int		i;

	i = 0;
	while (cmd->args[index][i])
	{
		if (cmd->lint[index][i] != _DOLLARED)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	arg_is_empty(t_cmd *cmd, int index)
{
	int		i;

	i = 0;
	while (cmd->args[index][i])
	{
		if (cmd->lint[index][i] != _EMPTY_CHAR)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	space_in_arg(t_cmd *cmd, int i)
{
	while (i < cmd->arg_nbr && cmd->args && cmd->args[i] && is_redir(cmd, i))
		i++;
	if (cmd->args && cmd->args[i] && !is_redir(cmd, i))
		i += 2;
	if (cmd->args && cmd->args[i] && is_redir(cmd, i) && is_pipe(cmd, i))
		return (SUCCESS);
	else if (cmd->args && cmd->args[i])
		return (space_in_arg(cmd, i));
	else
		return (FAILURE);
}



int	open_file(t_cmd *cmd, int start, int separator)
{
	int		arg_index;
	int		file_fd;

	file_fd = -1;
	arg_index = redir_in_args(cmd, start) + 1;
	if (!space_in_arg(cmd, cmd->arg_index))
		return (print_error(NULL, NULL, \
			"ambiguous redirect", -1));
	if (separator == R_RIGHT)
		file_fd = open(cmd->args[arg_index], \
			O_WRONLY | O_TRUNC | O_CREAT, 00644);
	else if (separator == R_RIGHTD)
		file_fd = open(cmd->args[arg_index], \
			O_WRONLY | O_APPEND | O_CREAT, 00644);
	else if (separator == R_LEFT)
	{
		file_fd = open(cmd->args[arg_index], O_RDONLY, 00644);
		if (file_fd == -1)
			return (print_error(NULL, cmd->args[arg_index], \
				"no such file or directory", -2));
	}
	return (file_fd);
}
