/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:59:23 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/18 19:50:33 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_std(pid_t *saved_stdin, pid_t *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
}

int	create_next_file(t_cmd *cmd, int start)
{
	int		file_fd;

	if (start >= cmd->arg_nbr)
		return (-1);
	if (cmd->args && !compare_size(cmd->args[start], "<") && \
		cmd->lint[start][0] == _SEP)
	{
		file_fd = open_file(cmd, start, R_LEFT);
		dup2(file_fd, STDIN_FILENO);
	}
	else if (cmd->args && !compare_size(cmd->args[start], ">") && \
		cmd->lint[start][0] == _SEP)
	{
		file_fd = open_file(cmd, start, R_RIGHT);
		dup2(file_fd, STDOUT_FILENO);
	}
	else if (cmd->args && !compare_size(cmd->args[start], ">>") && \
		cmd->lint[start][0] == _SEP)
	{
		file_fd = open_file(cmd, start, R_RIGHTD);
		dup2(file_fd, STDOUT_FILENO);
	}
	else
		file_fd = -1;
	return (file_fd);
}

int	create_files(t_cmd *cmd)
{
	int	index;
	int	file_fd;
	int	before_last;
	int	limit;

	index = redir_in_args(cmd, cmd->arg_index);
	limit = pipe_in_args(cmd, cmd->arg_index);
	file_fd = create_next_file(cmd, index);
	if (file_fd == -2)
		return (-1);
	before_last = file_fd;
	index = redir_in_args(cmd, index + 1);
	while (file_fd != -1 && index < limit)
	{
		close(file_fd);
		file_fd = create_next_file(cmd, index);
		if (file_fd == -2)
			return (-1);
		if (file_fd == -1)
			break ;
		before_last = file_fd;
		index = redir_in_args(cmd, index + 1);
	}
	return (before_last);
}

void	skip_redirs(t_cmd *cmd)
{
	int	next_pipe;
	int	next_redir;

	next_pipe = pipe_in_args(cmd, cmd->arg_index);
	next_redir = redir_in_args(cmd, cmd->arg_index);
	if (next_redir >= next_pipe)
		return ;
	while (cmd->arg_index < cmd->arg_nbr && cmd->args && \
		cmd->args[cmd->arg_index] && is_redir(cmd, cmd->arg_index))
		cmd->arg_index++;
	while (cmd->arg_index < cmd->arg_nbr && cmd->args && \
		cmd->args[cmd->arg_index] && !is_redir(cmd, cmd->arg_index))
	{
		cmd->arg_index += 2;
		while (cmd->args && cmd->args[cmd->arg_index] && \
			!arg_is_dollared(cmd, cmd->arg_index))
			cmd->arg_index++;
	}
}

int	redir(t_info *info, t_cmd *cmd, int child)
{
	int		file_fd;
	int		pipe;

	file_fd = create_files(cmd);
	if (file_fd == -1)
	{
		dup2(info->saved_stdin, STDIN_FILENO);
		dup2(info->saved_stdin, STDOUT_FILENO);
		return (FAILURE);
	}
	if (cmd->bui <= 8)
		info->built_in[cmd->bui](info, cmd);
	pipe = pipe_in_args(cmd, cmd->arg_index);
	dup2(info->saved_stdin, STDIN_FILENO);
	dup2(info->saved_stdin, STDOUT_FILENO);
	close(file_fd);
	if (pipe < cmd->arg_nbr && !child)
		exec_cmd(info, cmd, TRUE, child);
	return (SUCCESS);
}
