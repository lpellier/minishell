/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colon_and_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:13:27 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/15 16:33:19 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_exceptions(int quote, int dquote)
{
	if (quote % 2 != 0 || dquote % 2 != 0)
		return (1);
	else
		return (0);
}

int	redirs_first(t_cmd *cmd) 
{
	int		i;

	if (is_redir(cmd, 0))
		return (FAILURE);
	i = 0;
	while (i < cmd->arg_nbr && cmd->args && cmd->args[i] && !is_redir(cmd, i))
	{
		i += 2;
		while (cmd->args && cmd->args[i] && !arg_is_dollared(cmd, i))
			i++;
	}
	if (cmd->args && cmd->args[i] && is_redir(cmd, i) && is_pipe(cmd, i))
		return (SUCCESS);
	return (FAILURE);
}

int	redir_in_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		if (!is_redir(cmd, i))
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}
