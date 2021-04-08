/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:35:35 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/08 16:53:40 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_cmd(char *line, t_cmd *cmd, int index)
{
	char	**words;
	int		block_end;
	int		i;

	i = 0;
	block_end = check_if_block(index);
	if (block_end >= 0)
		cmd->cmd = ft_strndup(line, block_end - index);
	else
	{
		if (line && line[i] && !ft_cinset(line[i], SEPARATOR))
			return (0);
		words = ft_split(line, 32);
		while (words && words[0][i])
		{
			if (words[0][i] >= 65 && words[0][i] <= 90)
				words[0][i] += 32;
			i++;
		}
		if (words && words[0])
			cmd->cmd = ft_strdup(words[0]);
		free_tab(&words);
	}
	return (ft_strlen(cmd->cmd));
}

/*
** recursive function that allows creating as many
** linked lists as there are commands
** is there another cmd determined by whether there is a pipe |
** or a semi-colon for now;
*/

// ATTENTION
// g_info.output = ft_strdup("");  => might cause an issue later

void	read_cmd(char *line, int index, int index_cmd)
{
	t_cmd	*cmd;

	cmd = ft_list_at(g_info.cmd_head, index_cmd)->data;
	index += spaces(&line[index]);
	index += get_cmd(&line[index], cmd, index);
	index += spaces(&line[index]);
	index += get_option(&line[index], cmd, index);
	index += spaces(&line[index]);
	index += get_input(&line[index], cmd, index);
	index += spaces(&line[index]);
	compare_cmd(cmd);
	print_cmd_info(cmd);
	if (cmd->cmd && cmd->bui == 9)
		g_info.output = ft_strjoin(ft_strjoin("minisheh: ", cmd->cmd), \
			": command not found\n");
	else if ((!line || (line && !line[index])) && cmd->bui == 9)
		g_info.output = ft_strdup("");
	else if (!is_pipe(line[index]))
		pipe_for_exec(index_cmd, line, index, PIPE);
	else if (!is_colon(line[index]))
	{
		if (cmd->bui == 8)
			pipe_for_exec(index_cmd, line, index, NOTHING);
		else
			g_info.cmd_status = g_info.built_in[cmd->bui](index_cmd);
		ft_list_push_back(&g_info.cmd_head, create_cmd_struct());
		read_cmd(line, index + 1, index_cmd + 1);
	}
	else if (!is_redir_l(line[index]))
		redir(index_cmd, line, index, R_LEFT);
	else if (!is_redir_r(line[index]) && line[index + 1] && \
		!is_redir_r(line[index + 1]))
		redir(index_cmd, line, index, R_RIGHTD);
	else if (!is_redir_r(line[index]))
		redir(index_cmd, line, index, R_RIGHT);
	else if (cmd->bui == 8)
		pipe_for_exec(index_cmd, line, index, NOTHING);
	else
		g_info.cmd_status = g_info.built_in[cmd->bui](index_cmd);
}
