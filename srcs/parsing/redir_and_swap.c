/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:31:32 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/06 14:34:01 by tefroiss         ###   ########.fr       */
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

	i = cmd->arg_index;
	while (cmd->args && !is_redir(cmd, i))
		i += 2;
	if (i == 0)
		return ;
	while (i > 0)
	{
		swap_args(cmd, i, i - 1);
		i--;
	}
}

void	modify_line_redir(t_cmd *cmd, int i)
{
	int		redir_pos;

	while (cmd->args && cmd->args[i] && is_redir(cmd, i))
		i++;
	redir_pos = i;
	i += 2;
	while (cmd->args && cmd->args[i] && is_redir(cmd, i))
	{
		swap_args(cmd, redir_pos, i);
		swap_args(cmd, i, i - 1);
		redir_pos++;
		i++;
	}
	if (cmd->args && cmd->args[i])
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
