/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:24:47 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/27 00:46:30 by lpellier         ###   ########.fr       */
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

int		count_args(t_info *info, char *line, int *lint)
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

char	**split_by_empty(t_info *info, char *line, int arg_nbr)
{
	char	**split;
	int		line_index;
	int		word_index;
	int		word_count;

	line_index = 0;
	word_count = 0;
	if (ft_calloc((void **)&split, arg_nbr + 1, sizeof(char *)))
		return (NULL);
	while (line[line_index] && info->lint[line_index + info->lint_index] != -1)
	{
		if (info->lint[line_index + info->lint_index] == _EMPTY_CHAR && \
			!is_empty_or_void(info->lint[line_index + info->lint_index + 1]))
		{
			split[word_count] = ft_strdup("");
			word_count++;
			line_index++;
			while (info->lint[line_index + info->lint_index] == _EMPTY_CHAR)
				line_index++;
		}
		word_index = line_index;
		while (line[word_index] && info->lint[word_index + info->lint_index] != -1 && \
			info->lint[word_index + info->lint_index] != _EMPTY)
			word_index++;
		if (word_index - line_index > 0)
		{
			split[word_count] = ft_substr(line, line_index, word_index - line_index);
			line_index += word_index - line_index;
			word_count++;
		}
		line_index++;
	}
	info->lint_index += line_index + 1;
	info->line_index = line_index;
	split[word_count] = NULL;
	return (split);
}

// int		separator_in_args(char **args)
// {
// 	int		ret;
// 	int		i;

// 	ret = -1;
// 	i = 0;
// 	while (args && args[i])
// 	{
		
// 	}
// }

/*
** recursive function that allows creating as many
** linked lists as there are commands
** is there another cmd determined by whether there is a pipe |
** or a semi-colon for now;
*/

void	read_cmd(t_info *info, char *cmd_line)
{
	// int		sep_arg;
	t_cmd	*cmd;

	cmd = ft_list_at(info->cmd_head, info->index_cmd)->data;
	cmd->arg_nbr = count_args(info, cmd_line, info->lint);
	cmd->args = split_by_empty(info, cmd_line, cmd->arg_nbr);
	// sep_arg = separator_in_args(cmd->args);
	compare_cmd(info, cmd);
	if (info->debug_option)
		print_cmd_info(cmd);
	if (cmd->args && cmd->args[0] && !compare_size(cmd->args[0], ".") && cmd->bui == 9)
		ft_printf("minisheh: .: usage: . filename [arguments]\n");
	else if (cmd->args && cmd->args[0] && cmd->bui == 9)
		ft_printf("minisheh: %s: command not found\n", cmd->args[0]);
	// else if (cmd_line[info->line_index] == 124 && info->lint[info->lint_index] == _TOKEN)
	// 	pipe_for_exec(info, index, PIPE);
	// else if (!is_redir_l(line[index]))
	// 	redir(line, index, R_LEFT);
	// else if (!is_redir_r(line[index]) && line[index + 1] && \
	// 	!is_redir_r(line[index + 1]))
	// 	redir(line, index, R_RIGHTD);
	// else if (!is_redir_r(line[index]))
	// 	redir(line, index, R_RIGHT);
	// else if (cmd->bui == 8)
	// 	pipe_for_exec(line, index, NOTHING);
	// else if (!cmd->cmd)
	// 	return ;
	// else
	// 	update_cmd_status(info, info->built_in[cmd->bui]());
}
