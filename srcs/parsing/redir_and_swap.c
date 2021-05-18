/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:31:32 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/18 20:13:47 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir(t_cmd *cmd, int i)
{
	if (!cmd->args || i >= cmd->arg_nbr || !cmd->args[i] || !cmd->lint[i])
		return (FAILURE);
	if (cmd->lint[i][0] == _SEP && \
		(!compare_size(cmd->args[i], "<") || cmd->args[i][0] == '>'))
		return (SUCCESS);
	return (FAILURE);
}

void	swap_args(t_cmd *cmd, int arg_index_one, int arg_index_two)
{
	char	*c_tmp;
	int		*i_tmp;

	c_tmp = cmd->args[arg_index_one];
	i_tmp = cmd->lint[arg_index_one];
	cmd->args[arg_index_one] = cmd->args[arg_index_two];
	cmd->lint[arg_index_one] = cmd->lint[arg_index_two];
	cmd->args[arg_index_two] = c_tmp;
	cmd->lint[arg_index_two] = i_tmp;
}

void	move_first_redir(t_cmd *cmd)
{
	int		i;
	int		saved_i;
	int		count;
	int		limit;

	i = cmd->arg_index;
	while (cmd->args && !is_redir(cmd, i))
		i += 2;
	saved_i = i;
	limit = sep_in_args(cmd, i);
	count = 0;
	while (cmd->args[i] && i < limit)
	{
		count++;
		i++;
	}
	if (saved_i == 0)
		return ;
	swap_first_redir(cmd, i, saved_i, count);
}

void	modify_line_redir(t_cmd *cmd, int i)
{
	int		redir_pos;
	int		next_pipe;

	next_pipe = pipe_in_args(cmd, i);
	while (i < next_pipe && cmd->args && cmd->args[i] && is_redir(cmd, i))
		i++;
	redir_pos = i;
	i += 2;
	while (cmd->args && cmd->args[i] && i < next_pipe && is_redir(cmd, i))
	{
		swap_args(cmd, redir_pos, i);
		swap_args(cmd, i, i - 1);
		redir_pos++;
		i++;
	}
	if (cmd->args && cmd->args[i] && i < next_pipe)
		modify_line_redir(cmd, i);
}

int	is_pipe(t_cmd *cmd, int i)
{
	if (!cmd->args || i >= cmd->arg_nbr || !cmd->args[i] || !cmd->lint[i])
		return (FAILURE);
	if (cmd->lint[i][0] == _SEP && \
		!compare_size(cmd->args[i], "|"))
		return (SUCCESS);
	return (FAILURE);
}
