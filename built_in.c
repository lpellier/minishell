/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:05:33 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/23 11:03:48 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** outputs input
*/

int			ft_echo(int index_cmd)
{
	t_cmd	*cmd;

	cmd = ft_list_at(info.cmd_head, index_cmd)->data;
	if (!cmd->input)
		ft_printf("\n");
	else
		ft_printf("%s\n", cmd->input);
	return (SUCCESS);
}

void		store_output(int index_cmd)
{
	char	*str;
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_list_at(info.cmd_head, index_cmd)->data;
	get_next_line(STDIN_FILENO, &str);
	info.output = ft_strdup(str);
	if (cmd->bui != 1 && cmd->bui != 9)
		info.output = ft_strjoin(str, "\n");
	else
		info.output = ft_strdup(str);
	while (get_next_line(STDIN_FILENO, &str))
	{
		if (cmd->bui != 1 && cmd->bui != 9)
			info.output = ft_strjoin(ft_strjoin(info.output, str), "\n");
		else
			info.output = ft_strjoin(info.output, str);
	}
	if (str)
		free(str);
	str = NULL;
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

int			pipe_for_exec(int index_cmd, char *line, int index, int piped)
{
	int		pipefd[2];
	pid_t	cpid;
	pid_t	saved_stdin;
	pid_t	saved_stdout;
	t_cmd	*cmd;
	int		status;

	cmd = ft_list_at(info.cmd_head, index_cmd)->data;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	cpid = fork();
	if (cpid == -1)
		exit(EXIT_FAILURE);
	if (cpid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		_exit((info.built_in[cmd->bui])(index_cmd));
	}
	else
	{
		waitpid(cpid, &status, 0);
		info.cmd_status = status;
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		if (piped)
		{
			ft_list_push_back(&info.cmd_head, create_cmd_struct());
			read_cmd(line, index + 1, index_cmd + 1);
		}
		else
			store_output(index_cmd);
		if (cmd->bui == 2)
			info.crashed = TRUE;
		close(pipefd[0]);
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		return (EXIT_SUCCESS);
	}
}

/*
** outputs input without \n
*/

int			ft_echo_n(int index_cmd)
{
	t_cmd	*cmd;

	cmd = ft_list_at(info.cmd_head, index_cmd)->data;
	if (cmd->input)
		ft_printf("%s\033[47m\033[30m%%\033[39m\033[49m", cmd->input);
	return (SUCCESS);
}

/*
** exits terminal
*/

int			ft_exit(int index_cmd)
{
	(void)index_cmd;
	info.crashed = TRUE;
	ft_printf("exit\n");
	return (SUCCESS);
}

/*
** outputs current path
*/

int			ft_pwd(int index_cmd)
{
	char	cwd[PATH_MAX];

	(void)index_cmd;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	return (SUCCESS);
}

/*
** exports a variable to environment
** need to figure out return codes for built in
*/

int			ft_export(int index_cmd)
{
	t_cmd	*cmd;
	char	**key_value;

	cmd = ft_list_at(info.cmd_head, index_cmd)->data;
	if (!cmd->input || !ft_strchr(cmd->input, '='))
		return (FAILURE);
	key_value = ft_split(cmd->input, "=");
	if (!key_value[1])
		return (FAILURE);
	ft_list_push_back(&info.env_head,
		create_env_struct(key_value[0], key_value[1]));
	free(key_value);
	key_value = NULL;
	return (SUCCESS);
}
