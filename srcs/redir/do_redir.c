/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:59:23 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/27 17:33:29 by lpellier         ###   ########.fr       */
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

int	redir(t_info *info, t_cmd *cmd, int separator)
{
	int		file_fd;
	pid_t	saved_stdin;
	pid_t	saved_stdout;

	// file_fd = open_file(info, separator, line, &index);
	file_fd = 0;
	if (file_fd == -1)
		return (FAILURE);
	save_std(&saved_stdin, &saved_stdout);
	if (separator == R_LEFT)
		dup2(file_fd, STDIN_FILENO);
	else if (separator == R_RIGHT || separator == R_RIGHTD)
		dup2(file_fd, STDOUT_FILENO);
	exec_cmd(info, cmd);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(file_fd);
	return (SUCCESS);
}
