/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colon_and_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:13:27 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/21 18:27:06 by lpellier         ###   ########.fr       */
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

void	swap_first_redir(t_cmd *cmd, int i, int saved_i, int count)
{
	int	saved_count;

	saved_count = count;
	while (count)
	{
		i = saved_i;
		while (i > 0)
		{
			swap_args(cmd, i, i - 1);
			i--;
		}
		count--;
		saved_i++;
	}
	i = 0;
	while (saved_count / 2)
	{
		swap_args(cmd, i, saved_count - 1);
		saved_count--;
		i++;
	}
}

int	parent_process(t_info *info, t_cmd *cmd, pid_t cpid, int pipefd[2])
{
	int	saved_status;

	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	waitpid(cpid, NULL, 1);
	saved_status = exec_cmd(info, cmd, TRUE, FALSE);
	close(pipefd[0]);
	return (saved_status % 255);
}
