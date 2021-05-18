/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_dollar_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:37:56 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/18 20:16:32 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (SUCCESS);
	return (FAILURE);
}

int	str_isalpha_withminus(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '-')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	multiple_args_after_redir(t_cmd *cmd, int i)
{
	while (i < cmd->arg_nbr && cmd->args && cmd->args[i] && is_redir(cmd, i))
		i++;
	if (cmd->args && cmd->args[i] && !is_redir(cmd, i))
		i += 2;
	while (i < cmd->arg_nbr && cmd->args && \
		cmd->args[i] && !arg_is_dollared(cmd, i))
		i++;
	if (cmd->args && cmd->args[i] && is_redir(cmd, i) && is_pipe(cmd, i))
		return (SUCCESS);
	else if (cmd->args && cmd->args[i])
		return (multiple_args_after_redir(cmd, i + 1));
	else
		return (FAILURE);
}

int	dollar_in_arg(t_cmd *cmd, int i, int *start)
{
	while (cmd->args[i] && cmd->args[i][*start])
	{
		if (cmd->args[i][*start] == DOLLAR && \
			(cmd->lint[i][*start] == _DOLLAR || \
			cmd->lint[i][*start] == _DQUOTED))
			return (*start);
		*start += 1;
	}
	return (-1);
}

void	check_for_dollars(t_info *info, char *cmd_line)
{
	int		i;
	int		li;

	i = 0;
	li = info->lint_index;
	while (cmd_line[i])
	{
		if (cmd_line[i] == DOLLAR && \
			(info->lint[li] == _DOLLAR || info->lint[li] == _DQUOTED))
			dollar(info, cmd_line, i);
		i++;
		li++;
	}
}
