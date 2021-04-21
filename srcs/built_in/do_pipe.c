/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:41:42 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/21 12:38:40 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	check_cpid_zero(int separator, int index_cmd, t_cmd *cmd, int *pipefd)
{
	close(pipefd[0]);
	if (separator == PIPE)
		dup2(pipefd[1], STDOUT_FILENO);
	else
		close(pipefd[1]);
	g_info->status = (g_info->built_in[cmd->bui])(index_cmd);
	return (g_info->status);
}

void	check_pipe(int *pipefd, pid_t cpid)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	if (g_info->kill)
	{
		kill(cpid, SIGINT);
		g_info->sig_status = 130;
	}
	waitpid(cpid, &g_info->status, 0);
	init_termcap();
	g_info->bin_running = FALSE;
	g_info->cmd_status = g_info->status % 255;
}

void	check_separator(int separator, char *line, int index, int index_cmd)
{
	if (separator == PIPE)
	{
		while (!ft_cinset(line[index], SEPARATOR))
			index++;
		ft_list_push_back(&g_info->cmd_head, create_cmd_struct());
		read_cmd(line, index, index_cmd + 1);
	}
}

int	pipe_for_exec(int index_cmd, char *line, int index, int separator)
{
	int		pipefd[2];
	pid_t	cpid;
	t_cmd	*cmd;
	pid_t	saved_stdin;
	pid_t	saved_stdout;

	g_info->bin_running = TRUE;
	cmd = ft_list_at(g_info->cmd_head, index_cmd)->data;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	restore_term();
	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	cpid = fork();
	if (cpid == -1)
		exit(EXIT_FAILURE);
	if (cpid == 0)
		_exit(check_cpid_zero(separator, index_cmd, cmd, pipefd));
	else
	{
		check_pipe(pipefd, cpid);
		check_separator(separator, line, index, index_cmd);
		return (print_std(saved_stdin, saved_stdout, pipefd[0]));
	}
}
