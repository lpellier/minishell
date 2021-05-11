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

void	init_info_n_term(t_info *info)
{
	info->terminfo.echo_padding_x = 0;
	info->cursor.posy = 0;
	info->cursor.posx = info->terminfo.prompt_len + \
		info->terminfo.echo_padding_x;
}

int	read_keys(t_info *info, char key, t_history *cur)
{
	while (key != '\n')
	{
		if (read(STDIN_FILENO, &key, 1) == -1)
			return (FAILURE);
		if (g_signal->kill == 130)
		{
			update_cmd_status(info, g_signal->kill);
			g_signal->kill = FALSE;
			init_info_n_term(info);
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
		else if (key != '\n' && ft_cinset(key, WHITESPACE) && ft_isprint(key))
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
	info->terminfo.prompt_len += info->terminfo.echo_padding_x % info->terminfo.col;
	if (read_keys(info, key, cur))
	{
		update_cmd_status(info, 1);
		return (FAILURE);
	}
	if (info->terminfo.echo_padding_x > 0)
		info->terminfo.echo_padding_x = 0;
	return (SUCCESS);
}

// bslashes within a dquote only work if the following character is a 
//	dollar, a dquote,(a backquote) or another bslash
// not sure whether backquotes should be supported or not 

// other warning : when used solo, a backslash lets you finish a 
//	command in line under current one. 
// should i implement this ?

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

void	set_n_first(t_info *info, int first)
{
	if (first)
		info->history_head = ft_create_elem(create_history_struct());
	else
		ft_list_push_front(&info->history_head, create_history_struct());
	read_line(info);
	set_lint(info, info->lint);
	ft_printf("\n");
}

void	process_line(t_info *info, int first)
{
	int		crashed;

	crashed = FALSE;
	set_n_first(info, first);
	if (transform_line(info, 0, 0, 0))
	{
		update_cmd_status(info, print_error(NULL, \
			"parsing error", "number of quotes should be even", 1));
		return ;
	}
	if (check_syntax(info))
	{
		update_cmd_status(info, 2);
		return ;
	}
	info->cmd_tab = split_by_colon(info, info->line, info->lint);
	info->index_cmd = 0;
	while (info->cmd_tab && info->cmd_tab[info->index_cmd])
	{
		read_cmd(info, info->cmd_tab[info->index_cmd]);
		info->index_cmd += 1;
	}
	ft_list_clear(info->cmd_head, free_cmd_struct);
	free_tab(&info->cmd_tab);
}
