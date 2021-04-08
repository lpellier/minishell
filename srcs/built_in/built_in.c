/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:05:33 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/08 11:42:59 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	store_output(int index_cmd)
{
	char	*str;
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_list_at(g_info.cmd_head, index_cmd)->data;
	get_next_line(STDIN_FILENO, &str);
	g_info.output = ft_strdup(str);
	if (cmd->bui != 1 && cmd->bui != 9)
		g_info.output = ft_strjoin(str, "\n");
	else
		g_info.output = ft_strdup(str);
	while (get_next_line(STDIN_FILENO, &str))
	{
		if (cmd->bui != 1 && cmd->bui != 9)
			g_info.output = ft_strjoin(ft_strjoin(g_info.output, str), "\n");
		else
			g_info.output = ft_strjoin(g_info.output, str);
	}
	if (str)
		free(str);
	str = NULL;
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
	index += spaces(&line[index]);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (separator == R_LEFT)
		dup2(file_fd, STDIN_FILENO);
	else if (separator == R_RIGHT || separator == R_RIGHTD)
		dup2(file_fd, STDOUT_FILENO);
	if (line[index] && !is_redir_l(line[index]))
		redir(index_cmd, line, index, R_LEFT);
	else if (line[index] && !is_redir_r(line[index]) && line[index + 1] \
			&& !is_redir_r(line[index + 1]))
		redir(index_cmd, line, index, R_RIGHTD);
	else if (line[index] && !is_redir_r(line[index]))
		redir(index_cmd, line, index, R_RIGHT);
	else if (cmd->bui == 8)
		pipe_for_exec(index_cmd, line, index, NOTHING);
	else if (cmd->bui == 9)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(file_fd);
		return (SUCCESS);
	}
	else
		g_info.built_in[cmd->bui](index_cmd);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(file_fd);
	return (SUCCESS);
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
	pid_t	saved_stdin;
	pid_t	saved_stdout;
	t_cmd	*cmd;
	int		status;

	cmd = ft_list_at(g_info.cmd_head, index_cmd)->data;
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
		_exit((g_info.built_in[cmd->bui])(index_cmd));
	}
	else
	{
		waitpid(cpid, &status, 0);
		g_info.cmd_status = status - 255;
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		if (separator == PIPE)
		{
			while (!ft_cinset(line[index], SEPARATOR))
				index++;
			ft_list_push_back(&g_info.cmd_head, create_cmd_struct());
			read_cmd(line, index, index_cmd + 1);
		}
		else if (separator == NOTHING)
		{
			store_output(index_cmd);
			if (g_info.output)
			{
				ft_printf("%s", g_info.output);
				free(g_info.output);
			}
			g_info.output = NULL;
		}
		if (cmd->bui == 2)
			g_info.crashed = TRUE;
		close(pipefd[0]);
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		return (EXIT_SUCCESS);
	}
}

int	str_isalpha_withplus(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '+')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

char	last_char(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
		i++;
	if (i > 0)
		c = str[i - 1];
	else
		c = '\0';
	return (c);
}

/*
** exports a variable to environment
** need to figure out return codes for built in
*/

int	ft_export(int index_cmd)
{
	t_cmd	*cmd;
	t_env	*env_tmp;
	int		concat;
	char	**key_value;

	cmd = ft_list_at(g_info.cmd_head, index_cmd)->data;
	if (cmd->option)
	{
		ft_printf("minisheh: %s: %s: invalid option\n", cmd->cmd, cmd->option);
		return (FAILURE);
	}
	if (!cmd->input || !ft_strchr(cmd->input, '='))
		return (FAILURE);
	key_value = ft_split(cmd->input, '=');
	concat = 0;
	if (last_char(key_value[0]) == '+')
	{
		remove_char(key_value[0], ft_strlen(key_value[0]) - 1);
		concat = 1;
	}
	if (!key_value[1])
		return (FAILURE);
	if (str_isalpha_withplus(key_value[0]) || key_value[0][0] == '+')
	{
		ft_printf("minisheh: export: '%s': not a valid identifier\n", \
			cmd->input);
		return (FAILURE);
	}
	env_tmp = get_env_custom(key_value[0]);
	if (!env_tmp)
		ft_list_push_back(&g_info.env_head,
			create_env_struct(ft_strdup(key_value[0]), \
				ft_strdup(key_value[1])));
	else
		modify_env(key_value[0], key_value[1], concat);
	free_tab(&key_value);
	return (SUCCESS);
}
