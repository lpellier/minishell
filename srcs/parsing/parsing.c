/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:24:47 by lpellier          #+#    #+#             */
/*   Updated: 2021/05/22 12:46:51 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	bzero_lint(int *lint, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		lint[i] = -1;
		i++;
	}
}

void	init_cmd_lint(t_info *info, t_cmd *cmd)
{
	int		i;
	int		j;

	cmd->lint = NULL;
	if (ft_calloc((void **)&cmd->lint, cmd->arg_nbr, sizeof(int *)))
		return ;
	i = 0;
	j = info->lint_index;
	while (cmd->args && cmd->args[i] && i < cmd->arg_nbr)
	{
		cmd->lint[i] = NULL;
		if (ft_calloc((void **)&cmd->lint[i], LINE_MAX, sizeof(int)))
			return ;
		bzero_lint(cmd->lint[i], LINE_MAX);
		while (info->lint[j] != -1 && info->lint[j] == _EMPTY)
			j++;
		info->lnt_ind = 0;
		while (info->lint[j] != -1 && info->lint[j] != _EMPTY)
		{
			cmd->lint[i][info->lnt_ind] = info->lint[j];
			info->lnt_ind++;
			j++;
		}
		i++;
	}
}

int	continue_despite_error(t_info *info, t_cmd *cmd)
{
	int		next_sep;
	int		code;

	next_sep = sep_in_args(cmd, cmd->arg_index);
	code = print_error(NULL, cmd->args[cmd->arg_index], \
		"command not found", 127);
	if (next_sep > cmd->arg_index && next_sep <= cmd->arg_nbr)
	{
		cmd->arg_index = next_sep;
		code = exec_cmd(info, cmd, FALSE, FALSE);
	}
	return (code);
}

int	exec_cmd(t_info *info, t_cmd *cmd, int piped, int child)
{
	int		code;
	int		next_redir;
	int		next_pipe;

	code = 0;
	if (piped)
		update_arg_index(cmd, FALSE);
	compare_cmd(info, cmd);
	next_pipe = pipe_in_args(cmd, cmd->arg_index);
	next_redir = redir_in_args(cmd, cmd->arg_index);
	if (cmd->args && cmd->args[cmd->arg_index] && \
		!compare_size(cmd->args[cmd->arg_index], "."))
		code = print_error(NULL, ".", "filename argument required", 2);
	else if (cmd->args && cmd->args[cmd->arg_index] && \
		cmd->bui == 9 && is_redir(cmd, cmd->arg_index) && !child)
		code = continue_despite_error(info, cmd);
	else if (!is_pipe(cmd, next_pipe) && !child)
		code = pipe_for_exec(info, cmd);
	else if (!is_redir(cmd, next_redir))
		code = redir(info, cmd, child);
	else if (info->piped && next_pipe == cmd->arg_nbr)
		code = fork_last_pipe(info, cmd);
	else if (cmd->bui <= 8)
		code = info->built_in[cmd->bui](info, cmd);
	return (code);
}

void	read_cmd(t_info *info, char *cmd_line)
{
	t_cmd	*cmd;

	cmd = ft_list_at(info->cmd_head, info->index_cmd)->data;
	check_for_dollars(info, cmd_line);
	cmd->arg_nbr = count_args(info, cmd_line, info->lint);
	split_by_empty(info, cmd, cmd_line, cmd->arg_nbr);
	if (!redir_in_cmd(cmd))
	{
		while (!redirs_first(cmd))
			move_first_redir(cmd);
		while (!multiple_args_after_redir(cmd, 0))
			modify_line_redir(cmd, 0);
	}
	update_arg_index(cmd, TRUE);
	if (info->debug_option)
		print_cmd_info(cmd);
	restore_term(info);
	update_cmd_status(info, exec_cmd(info, cmd, FALSE, FALSE));
	dup2(info->saved_stdin, STDIN_FILENO);
	dup2(info->saved_stdout, STDOUT_FILENO);
	wait_for_children(info);
	interpret_errors(info);
}
