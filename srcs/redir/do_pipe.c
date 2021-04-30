/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:41:42 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/30 16:30:27 by lpellier         ###   ########.fr       */
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


void	interpret_errors(t_info *info)
{
	t_env	*code_env;
	t_cmd	*cmd;
	int		code;

	code_env = info->env_head->data;
	if (code_env)
	{
		code = ft_atoi(code_env->value);
		cmd = ft_list_at(info->cmd_head, info->index_cmd)->data;
		if (code == EACCES)
			ft_printf("minisheh: %s: permission denied\n", cmd->args[0]);
	}
}

int		get_child(t_info *info, t_cmd *cmd, pid_t cpid, int pipefd[2])
{
	int	c_status;

	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	exec_cmd(info, cmd, TRUE);
	waitpid(cpid, &c_status, 0);
	g_signal->bin_running = FALSE;
	init_termcap(info);
	return (c_status % 255);
}

int	child_process(t_info *info, t_cmd *cmd, int *pipefd)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	return ((info->built_in[cmd->bui])(info, cmd));
}

int	pipe_for_exec(t_info *info, t_cmd *cmd)
{
	int		pipefd[2];
	int		status;
	pid_t	cpid;
	pid_t	saved_stdin;
	pid_t	saved_stdout;

	g_signal->bin_running = TRUE;
	save_std(&saved_stdin, &saved_stdout);
	restore_term(info);
	if (pipe(pipefd) == -1)
		return (FAILURE);
	cpid = fork();
	if (cpid == -1)
		return (FAILURE);
	else if (cpid == 0)
		_exit(child_process(info, cmd, pipefd));
	else
	{
		status = get_child(info, cmd, cpid, pipefd);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(pipefd[0]);
		return (status);
	}
}
