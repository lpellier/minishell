/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:41:42 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/25 12:49:45 by lpellier         ###   ########.fr       */
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

int	child_process(int separator, t_cmd *cmd, int *pipefd)
{
	close(pipefd[0]);
	if (separator == PIPE)
		dup2(pipefd[1], STDOUT_FILENO);
	else
		close(pipefd[1]);
	g_info->status = (g_info->built_in[cmd->bui])();
	return (g_info->status);
}

void	get_child(int separator, pid_t cpid)
{
	//  || g_info->status != -1 ||
	if (g_info->kill || \
		(separator == PIPE && g_info->cmd_status == 127))
	{
		kill(cpid, SIGINT);
		g_info->sig_status = 130;
	}
	waitpid(cpid, &g_info->status, 0);
	init_termcap();
	g_info->bin_running = FALSE;
	g_info->cmd_status = g_info->status % 255;
}

void	check_pipe(int separator, char *line, int index)
{
	if (separator == PIPE)
	{
		while (!ft_cinset(line[index], SEPARATOR))
			index++;
		ft_list_push_back(&g_info->cmd_head, create_cmd_struct());
		g_info->index_cmd += 1;
		read_cmd(line, index);
	}
}

int	pipe_for_exec(char *line, int index, int separator)
{
	int		pipefd[2];
	pid_t	cpid;
	t_cmd	*cmd;
	pid_t	saved_stdin;
	pid_t	saved_stdout;

	g_info->bin_running = TRUE;
	cmd = ft_list_at(g_info->cmd_head, g_info->index_cmd)->data;
	save_std(&saved_stdin, &saved_stdout);
	restore_term();
	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	cpid = fork();
	if (cpid == -1)
		return (EXIT_FAILURE);
	else if (cpid == 0)
		_exit(child_process(separator, cmd, pipefd));
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		check_pipe(separator, line, index);
		get_child(separator, cpid);
		return (restore_std(saved_stdin, saved_stdout, pipefd[0]));
	}
}
