/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:59:23 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/20 18:52:08 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_std(pid_t *saved_stdin, pid_t *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
}

int	restore_std(pid_t saved_stdin, pid_t saved_stdout, int file_fd)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(file_fd);
	return (SUCCESS);
}

void	redir_something(char *line, int index, int index_cmd)
{
	if (line[index] && !is_redir_l(line[index]))
		redir(index_cmd, line, index, R_LEFT);
	else if (line[index] && !is_redir_r(line[index]) && line[index + 1] && \
		!is_redir_r(line[index + 1]))
		redir(index_cmd, line, index, R_RIGHTD);
	else if (line[index] && !is_redir_r(line[index]))
		redir(index_cmd, line, index, R_RIGHT);
}

int	redir(int index_cmd, char *line, int index, int separator)
{
	int		file_fd;
	pid_t	saved_stdin;
	pid_t	saved_stdout;
	t_cmd	*cmd;

	cmd = ft_list_at(g_info->cmd_head, index_cmd)->data;
	file_fd = open_file(separator, line, &index);
	if (file_fd == -1)
		return (FAILURE);
	index += spaces(&line[index], index);
	save_std(&saved_stdin, &saved_stdout);
	if (separator == R_LEFT)
		dup2(file_fd, STDIN_FILENO);
	else if (separator == R_RIGHT || separator == R_RIGHTD)
		dup2(file_fd, STDOUT_FILENO);
	if (line[index])
		redir_something(line, index, index_cmd);
	else if (cmd->bui == 8)
		pipe_for_exec(index_cmd, line, index, NOTHING);
	else if (cmd->bui == 9)
		return (restore_std(saved_stdin, saved_stdout, file_fd));
	else
		g_info->built_in[cmd->bui](index_cmd);
	return (restore_std(saved_stdin, saved_stdout, file_fd));
}
