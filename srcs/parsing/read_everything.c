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


void		modify_line_redir(char *str)
{
	(void)str;
	// int		i;
	// int		start;
	// int		count;
	// char	*tmp;

	// i = 0;
	// start = 0;
	// tmp = NULL;
	// while (str[i])
	// {
	// 	count = 0;
	// 	if (str[i] == BSLASH)
	// 		i++;
	// 	if (!is_redir_l(str[i]) || !is_redir_r(str[i]))
	// 	{
	// 		if (!start)
	// 			start = i;
	// 		while (str[i] && !ft_cinset(str[i], SEPARATOR))
	// 			i++;
	// 		count = count_until_redir(&str[i]);
	// 		tmp = ft_substr(str, i, count);
	// 		i += move_around(str, tmp, &start);
	// 		remove_words(str, i);
	// 		secure_free(tmp);
	// 	}
	// 	i++;
	// }
}

void	print_lint(t_info *info, int *lint)
{
	int	i;

	i = 0;
	ft_printf("\n--- LINT --- \n");
	while (i < LINE_MAX && lint[i] != -1)
	{
		if (lint[i] != _EMPTY)
			ft_printf("%d", lint[i]);
		else
			ft_printf(" ");
		i++;
	}
	ft_printf("\n");
	i = 0;
	while (info->line[i])
	{
		if (lint[i] != _EMPTY)
			ft_printf("%c", info->line[i]);
		else
			ft_printf(" ");
		i++;
	}
	ft_printf("\n------------ \n");
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
	// print_lint(info, info->lint);
	if (check_syntax(info))
		return ;
	cmd_tab = split_by_colon(info, info->line, info->lint);
	info->index_cmd = 0;
	while (cmd_tab && cmd_tab[info->index_cmd])
	{
		modify_line_redir(cmd_tab[info->index_cmd]);
		read_cmd(info, cmd_tab[info->index_cmd]);
		info->index_cmd += 1;
	}
	ft_list_clear(info->cmd_head, free_cmd_struct);
	free_tab(&cmd_tab);
}
