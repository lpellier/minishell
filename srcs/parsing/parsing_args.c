/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:23:04 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/06 20:24:47 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_args(t_info *info, char *line, int *lint)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (line[i] && lint[i + info->lint_index] != -1)
	{
		while (line[i] && lint[i + info->lint_index] == _EMPTY)
			i++;
		if (line[i] && lint[i + info->lint_index] != _EMPTY && \
			lint[i + info->lint_index] != -1)
		{
			count++;
			while (line[i] && lint[i + info->lint_index] != _EMPTY && \
				lint[i + info->lint_index] != -1)
				i++;
		}
		i++;
	}
	return (count);
}

int	redir_in_args(t_cmd *cmd, int start)
{
	while (cmd->args && cmd->args[start])
	{
		if (!is_redir(cmd, start))
			return (start);
		start++;
	}
	return (cmd->arg_nbr);
}

int	pipe_in_args(t_cmd *cmd, int start)
{
	while (cmd->args && cmd->args[start])
	{
		if (!is_pipe(cmd, start))
			return (start);
		start++;
	}
	return (cmd->arg_nbr);
}

int	sep_in_args(t_cmd *cmd, int start)
{
	while (cmd->args && cmd->args[start])
	{
		if (!is_pipe(cmd, start))
			return (start);
		else if (!is_redir(cmd, start))
			return (start);
		start++;
	}
	return (cmd->arg_nbr);
}

void	update_arg_index(t_cmd *cmd, int start)
{
	int		i;
	int		saved_index;

	i = cmd->arg_index;
	saved_index = i;
	while (cmd->args && cmd->args[i])
	{
		if (!is_pipe(cmd, i) || !is_redir(cmd, i))
		{
			cmd->arg_index = i + 1;
			if (start)
				cmd->arg_index = saved_index;
			cmd->limit_index = sep_in_args(cmd, cmd->arg_index);
			return ;
		}
		i += 1;
	}
	cmd->limit_index = cmd->arg_nbr;
}
