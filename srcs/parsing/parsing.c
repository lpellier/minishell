/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:24:47 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/28 16:45:05 by lpellier         ###   ########.fr       */
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

void	bzero_lint(int *lint, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		lint[i] = -1;
		i++;
	}
}

void	init_cmd_lint(t_info *info, t_cmd *cmd)
{
	int		i;
	int		lint_index;
	int		j;

	if (ft_calloc((void **)&cmd->lint, cmd->arg_nbr, sizeof(int *)))
		return ;
	i = 0;
	j  = 0;
	while (cmd->args && cmd->args[i] && i < cmd->arg_nbr)
	{
		if (ft_calloc((void **)&cmd->lint[i], ft_strlen(cmd->args[i]), sizeof(int)))
			return ;
		bzero_lint(cmd->lint[i], ft_strlen(cmd->args[i]));
		while (info->lint[j] != -1 && info->lint[j] == _EMPTY)
			j++;
		lint_index = 0;
		while (info->lint[j] != -1 && info->lint[j] != _EMPTY)
		{
			cmd->lint[i][lint_index] = info->lint[j];
			lint_index++;
			j++;
		}
		i++;
	}
}

void	split_by_empty(t_info *info, t_cmd *cmd, char *line, int arg_nbr)
{
	char	**split;
	int		line_index;
	int		word_index;
	int		word_count;

	line_index = 0;
	word_count = 0;
	if (ft_calloc((void **)&split, arg_nbr + 1, sizeof(char *)))
		return ;
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
	split[word_count] = NULL;
	cmd->args = split;
	init_cmd_lint(info, cmd);
	info->lint_index += line_index + 1;
	info->line_index = line_index;
}

int		set_arg_index(t_cmd *cmd, int next_pipe)
{
	int		arg_index;
	
	arg_index = 0;
	if (cmd->recursive_index)
		arg_index = cmd->recursive_index + 1;
	while (cmd->args && cmd->args[arg_index])
	{
		if (cmd->lint[arg_index][0] == _TOKEN && !compare_size(cmd->args[arg_index], "|"))
			return (arg_index);
		arg_index++;
	}
	if (next_pipe)
		return (cmd->arg_nbr);
	return (0);
}

int	exec_cmd(t_info *info, t_cmd *cmd)
{
	int		arg_index;

	arg_index = 0;
	if (cmd->recursive_index)
		arg_index = cmd->recursive_index + 1;
	compare_cmd(info, cmd);
	cmd->recursive_index = set_arg_index(cmd, FALSE);
	cmd->next_pipe = set_arg_index(cmd, TRUE);
	if (cmd->args && cmd->args[arg_index] && !compare_size(cmd->args[arg_index], "."))
		return (print_error(NULL, ".", "filename argument required"));
	else if (cmd->args && cmd->args[arg_index] && cmd->bui == 9)
		return (print_error(NULL, cmd->args[arg_index], "command not found"));
	else if (cmd->recursive_index && !compare_size(cmd->args[cmd->recursive_index], "|"))
		pipe_for_exec(info, cmd, PIPE);
	else if (cmd->recursive_index && !compare_size(cmd->args[cmd->recursive_index], "<"))
		redir(info, cmd, R_LEFT);
	else if (cmd->recursive_index && !compare_size(cmd->args[cmd->recursive_index], ">>"))
		redir(info, cmd, R_RIGHTD);
	else if (cmd->recursive_index && !compare_size(cmd->args[cmd->recursive_index], ">"))
		redir(info, cmd, R_RIGHT);
	else if (cmd->bui == 8)
		pipe_for_exec(info, cmd, NOTHING);
	else if (!cmd->args || !cmd->args[arg_index])
		return (FAILURE);
	else
		return(info->built_in[cmd->bui](info, cmd));
	return (SUCCESS);
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

void	rearrange_args(t_cmd *cmd)
{
	int		i;
	int		sub;
	int		limit;
	int		first;
	int		second;

	first = 0;
	limit = cmd->arg_nbr / 2;
	second = cmd->arg_nbr - 1;
	while (first < limit)
	{
		swap_args(cmd, first, second);
		first++;
		second--;
	}
	i = 0;
	first = 0;
	while (cmd->args && cmd->args[i])
	{
		if (cmd->lint[i][0] == _TOKEN && \
			!compare_size(cmd->args[i], "|"))
		{
			sub = 1;
			if ((i - first) % 2 == 0)
				sub = 0;
			while ((i - first - sub) / 2)
			{
				swap_args(cmd, first, i - 1);
				first++;
			}
			first = i + 1;
		}
		i++;
	}
	sub = 1;
	if ((i - first) % 2 == 0)
		sub = 0;
	while ((i - first - sub) / 2)
	{
		swap_args(cmd, first, i - 1);
		first++;
	}
}

int		pipe_in_cmd(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		if (cmd->lint[i][0] == _TOKEN && \
			!compare_size(cmd->args[i], "|"))
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

void	read_cmd(t_info *info, char *cmd_line)
{
	t_cmd	*cmd;

	cmd = ft_list_at(info->cmd_head, info->index_cmd)->data;
	cmd->arg_nbr = count_args(info, cmd_line, info->lint);
	split_by_empty(info, cmd, cmd_line, cmd->arg_nbr);
	if (!pipe_in_cmd(cmd))
		rearrange_args(cmd);
	if (info->debug_option)
		print_cmd_info(cmd);
	update_cmd_status(info, exec_cmd(info, cmd));
}
