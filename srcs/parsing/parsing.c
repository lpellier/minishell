/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:24:47 by lpellier          #+#    #+#             */
/*   Updated: 2021/05/04 19:31:07 by lpellier         ###   ########.fr       */
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

	cmd->lint = NULL;
	if (ft_calloc((void **)&cmd->lint, cmd->arg_nbr, sizeof(int *)))
		return ;
	i = 0;
	j  = info->lint_index;
	while (cmd->args && cmd->args[i] && i < cmd->arg_nbr)
	{
		cmd->lint[i] = NULL;
		if (ft_calloc((void **)&cmd->lint[i], LINE_MAX, sizeof(int)))
			return ;
		bzero_lint(cmd->lint[i], LINE_MAX);
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
	char	*tmp;
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
			if (ft_calloc((void **)&split[word_count], LINE_MAX, sizeof(char)))
				return ;
			ft_bzero(split[word_count], LINE_MAX);
			tmp = ft_substr(line, line_index, word_index - line_index);
			ft_strcpy(split[word_count], tmp);
			secure_free(tmp);
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

int		redir_in_args(t_cmd *cmd, int start)
{
	while (cmd->args && cmd->args[start])
	{
		if (!is_redir(cmd, start))
			return (start);
		start++;
	}
	return (cmd->arg_nbr);
}

int		pipe_in_args(t_cmd *cmd, int start)
{
	while (cmd->args && cmd->args[start])
	{
		if (!is_pipe(cmd, start))
			return (start);
		start++;
	}
	return (cmd->arg_nbr);
}

int		sep_in_args(t_cmd *cmd, int start)
{
	while (cmd->args && cmd->args[start])
	{
		if (!is_pipe(cmd, start))
			return (start);
		else if (!is_redir(cmd, start))
			return (start);
		start++;
	}
	return (cmd->arg_nbr);
}

void	update_arg_index(t_cmd *cmd, int start)
{
	int		i;
	int		saved_index;

	i = cmd->arg_index;
	saved_index = i;
	while (cmd->args && cmd->args[i])
	{
		if (!is_pipe(cmd, i) || !is_redir(cmd, i))
		{
			cmd->arg_index = i + 1;
			if (start)
				cmd->arg_index = saved_index;
			cmd->limit_index = sep_in_args(cmd, cmd->arg_index);
			return ;
		}
		i += 1;
	}
	cmd->limit_index = cmd->arg_nbr;
}

int	exec_cmd(t_info *info, t_cmd *cmd, int piped)
{
	int		code;
	int		next_redir;

	code = 0;
	if (piped)
		update_arg_index(cmd, FALSE);
	compare_cmd(info, cmd);
	next_redir = redir_in_args(cmd, cmd->arg_index);
	if (cmd->args && cmd->args[cmd->arg_index] && !compare_size(cmd->args[cmd->arg_index], "."))
		code = print_error(NULL, ".", "filename argument required", 2);
	else if (cmd->args && cmd->args[cmd->arg_index] && cmd->bui == 9 && is_redir(cmd, cmd->arg_index))
		code = print_error(NULL, cmd->args[cmd->arg_index], "command not found", 127);
	else if (cmd->limit_index && !is_pipe(cmd, cmd->limit_index))
		code = pipe_for_exec(info, cmd);
	else if (cmd->limit_index && !is_redir(cmd, cmd->limit_index))
		code = redir(info, cmd);
	else if (!cmd->args || !cmd->args[cmd->arg_index])
		code = 1;
	else
		code = info->built_in[cmd->bui](info, cmd);
	return (code);
}

int		redir_in_cmd(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		if (!is_redir(cmd, i))
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int		multiple_args_after_redir(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->args && cmd->args[i] && is_redir(cmd, i))
		i++;
	i += 2;
	if (i < cmd->arg_nbr && cmd->args && cmd->args[i] && \
		is_redir(cmd, i) && is_pipe(cmd, i) && arg_is_dollared(cmd, i))
		return (SUCCESS);
	return (FAILURE);
}

int		dollar_in_arg(t_cmd *cmd, int i, int *start)
{
	while (cmd->args[i] && cmd->args[i][*start])
	{
		if (cmd->args[i][*start] == DOLLAR && (cmd->lint[i][*start] == _DOLLAR || cmd->lint[i][*start] == _DQUOTED))
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
		if (cmd_line[i] == DOLLAR && (info->lint[li] == _DOLLAR || info->lint[li] == _DQUOTED))
			dollar(info, cmd_line, i);
		i++;
		li++;
	}
}

int		only_redirs(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->args && !is_redir(cmd, i))
		i += 2;
	if (cmd->args[i] && is_pipe(cmd, i))
		return (FAILURE);
	return (SUCCESS);
}

void	read_cmd(t_info *info, char *cmd_line)
{
	t_cmd	*cmd;
	pid_t	saved_stdin;
	pid_t	saved_stdout;

	cmd = ft_list_at(info->cmd_head, info->index_cmd)->data;
	check_for_dollars(info, cmd_line);
	cmd->arg_nbr = count_args(info, cmd_line, info->lint);
	split_by_empty(info, cmd, cmd_line, cmd->arg_nbr);
	if (!redir_in_cmd(cmd))
	{
		if (only_redirs(cmd))
			move_first_redir(cmd);
		while (!multiple_args_after_redir(cmd))
			modify_line_redir(cmd, 0);
	}
	update_arg_index(cmd, TRUE);
	if (info->debug_option)
		print_cmd_info(cmd);
	if (!only_redirs(cmd))
	{
		save_std(&saved_stdin, &saved_stdout);
		if (create_files(cmd) <= -1)
			update_cmd_status(info, FAILURE);
		else
			update_cmd_status(info, SUCCESS);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		while (cmd->args && !is_redir(cmd, cmd->arg_index))
			cmd->arg_index += 2;
		if (cmd->args && !is_pipe(cmd, cmd->arg_index))
			cmd->arg_index += 1;
		cmd->limit_index = sep_in_args(cmd, cmd->arg_index);
	}
	update_cmd_status(info, exec_cmd(info, cmd, FALSE));
	interpret_errors(info);
}
