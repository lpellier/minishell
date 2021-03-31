/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:24:47 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/31 14:48:27 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			get_input(char *line, t_cmd *cmd)
{
	int		index;

	index = 0;
	while (line[index] && is_pipe(line[index]) && is_colon(line[index]) && is_redir_l(line[index]) \
		&& is_redir_r(line[index]))
		index++;
	if (index >= 1)
		cmd->input = ft_strndup(line, index);
	else
		cmd->input = NULL;
	return (ft_strlen(cmd->input));
}

int			get_cmd(char *line, t_cmd *cmd)
{
	char	**words;

	words = ft_split(line, ' ');
	if (words && words[0] && words[1] && words[1][0] == '-')
		cmd->option = ft_strdup(words[1]);
	if (words && words[0])
		cmd->cmd = ft_strdup(words[0]);
	free_tab(&words);
	return (ft_strlen(cmd->cmd));
}

/*
** recursive function that allows creating as many
** linked lists as there are commands
** is there another cmd determined by whether there is a pipe |
** or a semi-colon for now;
*/

void		read_cmd(char *line, int index, int index_cmd)
{
	t_cmd	*cmd;

	cmd = ft_list_at(info.cmd_head, index_cmd)->data;
	index += spaces(&line[index]);
	index += get_cmd(&line[index], cmd);
	index += spaces(&line[index]);
	if (cmd->option)
		index += ft_strlen(cmd->option);
	index += spaces(&line[index]);
	index += get_input(&line[index], cmd);
	index += spaces(&line[index]);
	compare_cmd(cmd);
	// print_cmd_info(cmd);
	// check_sep(line, cmd);
	if (cmd->cmd && cmd->bui == 9)
		info.output = ft_strjoin(ft_strjoin("minisheh: ", cmd->cmd),
			": command not found\n");
	else if (cmd->bui == 9)
		info.output = ft_strdup(""); /* might cause an issue later */
	else if (!is_pipe(line[index]))
		pipe_for_exec(index_cmd, line, index, PIPE);
	else if (!is_colon(line[index]))
	{
		if (cmd->bui == 8)
			pipe_for_exec(index_cmd, line, index, NOTHING);
		else
			info.cmd_status = info.built_in[cmd->bui](index_cmd);
		if (info.output)
		{
			ft_printf("%s", info.output);
			free(info.output);
		}
		info.output = NULL;
		ft_list_push_back(&info.cmd_head, create_cmd_struct());
		read_cmd(line, index + 1, index_cmd + 1);
	}
	else if (!is_redir_l(line[index]))
		pipe_for_exec(index_cmd, line, index, R_LEFT);
	else if (!is_redir_r(line[index]) && line[index + 1] && !is_redir_r(line[index]))
		pipe_for_exec(index_cmd, line, index, R_RIGHTD);
	else if (!is_redir_r(line[index]))
		pipe_for_exec(index_cmd, line, index, R_RIGHT);
	else if (cmd->bui == 8)
		pipe_for_exec(index_cmd, line, index, NOTHING);
	else
		info.cmd_status = info.built_in[cmd->bui](index_cmd);
}
