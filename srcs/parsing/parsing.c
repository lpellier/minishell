/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:24:47 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/25 13:37:13 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	cmp_block(void *data, void *data_ref)
{
	t_block		*ptr;
	t_block		*ptr_ref;

	ptr = (t_block *)data;
	ptr_ref = (t_block *)data_ref;
	if (ptr->start == ptr_ref->start && ptr->end - ptr->start > 0)
		return (SUCCESS);
	else
		return (FAILURE);
}

int	check_if_block(int index)
{
	t_list		*ptr;
	t_block		*block;
	t_block		*data_ref;

	data_ref = create_block_struct(index, -1);
	ptr = ft_list_find(g_info->block_head, data_ref, \
		cmp_block);
	secure_free(data_ref);
	if (!ptr)
		return (-1);
	block = ptr->data;
	return (block->end);
}

/*
** recursive function that allows creating as many
** linked lists as there are commands
** is there another cmd determined by whether there is a pipe |
** or a semi-colon for now;
*/

int	ft_set_index(char *line, t_cmd *cmd, int index)
{
	index += spaces(&line[index], index);
	index += get_cmd(&line[index], cmd, index);
	if (cmd->cmd)
		index += 1;
	index += get_option(&line[index], cmd, index);
	if (cmd->option)
		index += 1;
	index += get_input(&line[index], cmd, index);
	if (cmd->input)
		index += 1;
	return (index);
}

void	read_cmd(char *line, int index)
{
	t_cmd	*cmd;

	cmd = ft_list_at(g_info->cmd_head, g_info->index_cmd)->data;
	index = ft_set_index(line, cmd, index);
	compare_cmd(cmd);
	if (g_info->debug_option)
		print_cmd_info(cmd);
	if (cmd->cmd && cmd->bui == 9)
		ft_printf("minisheh: %s: command not found\n", cmd->cmd);
	if (!is_pipe(line[index]))
		pipe_for_exec(line, index, PIPE);
	else if (!is_redir_l(line[index]))
		redir(line, index, R_LEFT);
	else if (!is_redir_r(line[index]) && line[index + 1] && \
		!is_redir_r(line[index + 1]))
		redir(line, index, R_RIGHTD);
	else if (!is_redir_r(line[index]))
		redir(line, index, R_RIGHT);
	else if (cmd->bui == 8)
		pipe_for_exec(line, index, NOTHING);
	else if (!cmd->cmd)
		return ;
	else
		g_info->cmd_status = g_info->built_in[cmd->bui]();
}
