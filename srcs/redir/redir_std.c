/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_std.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:24:27 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/06 12:07:45 by tefroiss         ###   ########.fr       */
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

int	space_in_arg(t_cmd *cmd, int index)
{
	int	next_redir;

	next_redir = redir_in_args(cmd, index);
	if (next_redir - index > 1)
		return (SUCCESS);
	if (!cmd->args[index] || !arg_is_empty(cmd, index))
		return (SUCCESS);
	return (FAILURE);
}

int	open_file(t_cmd *cmd, int start, int separator)
{
	int		arg_index;
	int		file_fd;

	file_fd = -1;
	arg_index = redir_in_args(cmd, start) + 1;
	if (!space_in_arg(cmd, arg_index))
		return (print_error(NULL, cmd->saved_env_arg, \
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
