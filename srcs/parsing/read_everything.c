/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 read_everything.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: tefroiss <tefroiss@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2021/03/24 11:17:51 by lpellier		   #+#	  #+#			  */
/*	 Updated: 2021/04/21 15:16:07 by tefroiss		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// info->cursor.posx - info->terminfo.prompt_len + 1 : this formula 
//	   lets me checkout where cursor is on string
// may be useful to insert or delete characters

int	read_keys(t_info *info, char key, t_history *cur)
{
	while (key != '\n')
	{
		if (read(STDIN_FILENO, &key, 1) == -1)
			return (FAILURE);
		if (g_signal->kill)
		{
			g_signal->kill = FALSE;
			info->terminfo.echo_padding = 0;
			info->cursor.posy = 0;
			info->cursor.posx = info->terminfo.prompt_len + info->terminfo.echo_padding;
			ft_bzero(info->line, ft_strlen(info->line));
			ft_bzero(cur->line, ft_strlen(cur->line));
		}
		if (key == 27 || key == 127)
			special_keys(info, key);
		else if (key == 4)
		{
			if (control_d(info))
				break ;
		}
		else if (key != '\n' && ft_cinset(key, WHITESPACE))
			add_key(info, info->line, key);
		if (info->cur_in_history == 0 || key == '\n')
			update_history(info, cur);
	}
	return (SUCCESS);
}

int	read_line(t_info *info)
{
	t_history	*cur;
	char		key;

	key = 0;
	ft_bzero(info->line, ft_strlen(info->line));
	cur = (t_history *)info->history_head->data;
	info->terminfo.prompt_len += info->terminfo.echo_padding;
	if (read_keys(info, key, cur))
	{
		update_cmd_status(info, 1);
		return (FAILURE);
	}
	if (info->terminfo.echo_padding > 0)
		info->terminfo.echo_padding = 0;
	return (SUCCESS);
}

// bslashes within a dquote only work if the following character is a 
//	dollar, a dquote,(a backquote) or another bslash
// not sure whether backquotes should be supported or not 

// other warning : when used solo, a backslash lets you finish a 
//	command in line under current one. 
// should i implement this ?


int			is_pipe(t_cmd *cmd, int i)
{
	if (!cmd->lint[i] || !cmd->args[i])
		return (FAILURE);
	if (cmd->lint[i][0] == _TOKEN && \
		!compare_size(cmd->args[i], "|"))
		return (SUCCESS);
	return (FAILURE);
}

int			is_redir(t_cmd *cmd, int i)
{
	if (i >= cmd->arg_nbr || !cmd->args[i] || !cmd->lint[i] || cmd->lint[i][0] == -1)
		return (FAILURE);
	if (cmd->lint[i][0] == _TOKEN && \
		(!compare_size(cmd->args[i], "<") || cmd->args[i][0] == '>'))
		return (SUCCESS);
	return (FAILURE);
}

void	swap_args(t_cmd *cmd, int arg_index_one, int arg_index_two)
{
	char	*c_tmp;
	int		*i_tmp;
	
	c_tmp = cmd->args[arg_index_one];
	i_tmp = cmd->lint[arg_index_one];
	cmd->args[arg_index_one] = cmd->args[arg_index_two];
	cmd->lint[arg_index_one] = cmd->lint[arg_index_two];
	cmd->args[arg_index_two] = c_tmp;
	cmd->lint[arg_index_two] = i_tmp;
}

typedef struct s_al
{
	char			*arg;
	int				*lint;
}					t_al;

void		move_arg(t_cmd *cmd, t_al *al, int index, int pos)
{
	int		*redir_lint;
	char	*redir_arg;
	int		*next_lint;
	char	*next_arg;

	redir_arg = cmd->args[pos];
	redir_lint = cmd->lint[pos];
	cmd->args[pos] = cmd->args[index];
	cmd->lint[pos] = cmd->lint[index];
	pos++;
	while (cmd->args && cmd->args[pos] && pos < cmd->arg_nbr - 1)
	{
		next_arg = cmd->args[pos];
		next_lint = cmd->lint[pos];
		cmd->args[pos] = redir_arg;
		cmd->lint[pos] = redir_lint;
		redir_arg = next_arg;
		redir_lint = next_lint;
		print_cmd_info(cmd);
		pos++;
	}
	ft_printf("\n");
	al->arg = redir_arg;
	al->lint = redir_lint;
	// cmd->args[pos] = redir_arg;
	// cmd->lint[pos] = redir_lint;
	// cmd->args[i] = c_tmp;
	// cmd->lint[i] = i_tmp;
}

void		modify_line_redir(t_cmd *cmd)
{
	t_al	*al;
	int		i;
	int		redir_pos;

	i = 0;
	al = NULL;
	if (ft_calloc((void **)&al, 1, sizeof(al)))
		return ;
	al->arg = NULL;
	al->lint = NULL;
	while (cmd->args && cmd->args[i] && is_redir(cmd, i))
		i++;
	redir_pos = i;
	i++;
	while (cmd->args && cmd->args[i])
	{
		i++;
		while (cmd->args && cmd->args[i] && is_redir(cmd, i))
		{
			move_arg(cmd, al, i, redir_pos);
			redir_pos++;
			i++;
		}
		if (al)
		{
			cmd->args[i - 1] = al->arg;
			cmd->lint[i - 1] = al->lint;
			secure_free(al);
		}
	}
}

/* 
 ** reads line using gnl and feeds t_cmd linked lists 
 ** i might modify our line in this function, as in removing 
 ** any unnecessary backslashes,
 ** quotes, double quotes etc..
 ** the point is to process our line so that it is readable 
 ** by our read_cmd function
 */

// currently building a way to know if blocks exist
// colons won't work right now BECUASE OF THE SPLIT

void	process_line(t_info *info, int first)
{
	char	**cmd_tab;
	int		crashed;

  	cmd_tab = NULL;
	crashed = FALSE;
	if (first)
		info->history_head = ft_create_elem(create_history_struct());
	else
		ft_list_push_front(&info->history_head, create_history_struct());
	read_line(info);
	set_lint(info, info->lint);
	ft_printf("\n");
	if (transform_line(info, 0, 0, 0))
	{
		update_cmd_status(info, 1);
		print_error(NULL, "parsing error", "number of quotes should be even");
		return ;
	}
	if (check_syntax(info))
		return ;
	cmd_tab = split_by_colon(info, info->line, info->lint);
	info->index_cmd = 0;
	while (cmd_tab && cmd_tab[info->index_cmd])
	{
		read_cmd(info, cmd_tab[info->index_cmd]);
		info->index_cmd += 1;
	}
	ft_list_clear(info->cmd_head, free_cmd_struct);
	free_tab(&cmd_tab);
}
