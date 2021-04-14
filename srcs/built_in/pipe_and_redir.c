/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:59:23 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/14 16:42:33 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_std(pid_t saved_stdin, pid_t saved_stdout, int file_fd)
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

	cmd = ft_list_at(g_info.cmd_head, index_cmd)->data;
	file_fd = open_file(separator, line, &index);
	if (file_fd == -1)
		return (FAILURE);
	index += spaces(&line[index], index);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (separator == R_LEFT)
		dup2(file_fd, STDIN_FILENO);
	else if (separator == R_RIGHT || separator == R_RIGHTD)
		dup2(file_fd, STDOUT_FILENO);
	if (line[index])
		redir_something(line, index, index_cmd);
	else if (cmd->bui == 8)
		pipe_for_exec(index_cmd, line, index, NOTHING);
	else if (cmd->bui == 9)
		return (print_std(saved_stdin, saved_stdout, file_fd));
	else
		g_info.built_in[cmd->bui](index_cmd);
	return (print_std(saved_stdin, saved_stdout, file_fd));
}

/*
** stores fd extremes from pipe : pipefd[0] is reading and pipefd[1] is writing
** cpid is child process id returned by fork
** status is basically the return code of any command,
** returned by waitpid, might be useful to store it
** saving std output and input fds
** forking so i can retrieve output of each function for piping
** closing useless writing extremity of pipe
** duplicating reading extremity of pipe into stdout
** exiting with cmd exit code, here built_in is only for binaries
** waits for child process and returns status
** closing useless reading extremity of pipe
** closing last pipe fd
** restoring stdout and stdin to original fds
*/

int	pipe_for_exec(int index_cmd, char *line, int index, int separator)
{
	int		pipefd[2];
	pid_t	cpid;
	t_cmd	*cmd;
	int		status;

	g_info.bin_running = TRUE;
	cmd = ft_list_at(g_info.cmd_head, index_cmd)->data;
	g_info.saved_stdin = dup(STDIN_FILENO);
	g_info.saved_stdout = dup(STDOUT_FILENO);
	restore_term();
	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	cpid = fork();
	if (cpid == -1)
		exit(EXIT_FAILURE);
	if (cpid == 0)
	{
		close(pipefd[0]);
		if (separator == PIPE)
			dup2(pipefd[1], STDOUT_FILENO);
		else
			close(pipefd[1]);
		status = (g_info.built_in[cmd->bui])(index_cmd);
		_exit(status);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		if (g_info.kill)
			kill(cpid, SIGINT);
		waitpid(cpid, &status, 0);
		init_termcap();
		g_info.bin_running = FALSE;
		g_info.cmd_status = status % 255;
		if (separator == PIPE)
		{
			while (!ft_cinset(line[index], SEPARATOR))
				index++;
			ft_list_push_back(&g_info.cmd_head, create_cmd_struct());
			read_cmd(line, index, index_cmd + 1);
		}
		return (print_std(g_info.saved_stdin, g_info.saved_stdout, pipefd[0]));
	}
}
