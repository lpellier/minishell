/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:59:23 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/29 13:48:03 by lpellier         ###   ########.fr       */
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

int		create_next_file(t_cmd *cmd, int start)
{
	int		file_fd;

	if (start >= cmd->arg_nbr)
		return (-1);
	if (cmd->args && !compare_size(cmd->args[start], "<") && \
		cmd->lint[start][0] == _TOKEN)
		file_fd = open_file(cmd, start, R_LEFT);
	else if (cmd->args && !compare_size(cmd->args[start], ">") && \
		cmd->lint[start][0] == _TOKEN)
		file_fd = open_file(cmd, start, R_RIGHT);
	else if (cmd->args && !compare_size(cmd->args[start], ">>") && \
		cmd->lint[start][0] == _TOKEN)
		file_fd = open_file(cmd, start, R_RIGHTD);
	else
		file_fd = -1;
	return (file_fd);
}

int	create_files(t_cmd *cmd)
{
	int	index;
	int file_fd;
	int	before_last;

	index = sep_in_args(cmd, cmd->arg_index);
	file_fd = create_next_file(cmd, index);
	before_last = file_fd;
	index = sep_in_args(cmd, index + 1);
	while (file_fd != -1 && index < cmd->arg_nbr)
	{
		close(file_fd);
		file_fd = create_next_file(cmd, index);
		if (file_fd == -1)
			break ;
		before_last = file_fd;
		index = sep_in_args(cmd, index + 1);
	}
	return (before_last);
	// sep in args returns pos of redir OR pipe (will have to remove that)
}

int	redir(t_info *info, t_cmd *cmd, int separator)
{
	int		file_fd;
	pid_t	saved_stdin;
	pid_t	saved_stdout;

	file_fd = create_files(cmd);
	if (file_fd == -1)
		return (print_error(NULL, NULL, "couldn't open requested file"));
	save_std(&saved_stdin, &saved_stdout);
	if (separator == R_LEFT)
		dup2(file_fd, STDIN_FILENO);
	else if (separator == R_RIGHT || separator == R_RIGHTD)
		dup2(file_fd, STDOUT_FILENO);
	info->built_in[cmd->bui](info, cmd);
	// maybe save arg_indexes for the call of this function
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(file_fd);
	return (SUCCESS);
}
