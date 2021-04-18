/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:17:51 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/18 16:21:27 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	arrow_or_delete(char key, char *line)
{
	if (key == 27)
		check_for_arrows(line);
	else if (key == 127)
		delete_key(line);
}

void	bzero_and_cpy(t_history *cur, char *line)
{
	ft_bzero(cur->line, ft_strlen(cur->line));
	ft_strcpy(cur->line, line);
}

// g_info.cursor.posx - g_info.prompt_len + 1 : this formula 
//     lets me checkout where cursor is on string
// may be useful to insert or delete characters

char	read_everything_suite(char key, char *line, t_history *cur)
{
	while (key != '\n')
	{
		get_pos(&g_info.cursor.posx, &g_info.cursor.posy);
		if (read(STDIN_FILENO, &key, 1) == -1)
			return (1);
		if (g_info.kill)
		{
			g_info.kill = FALSE;
			ft_bzero(line, ft_strlen(line));
			ft_bzero(cur->line, ft_strlen(cur->line));
		}
		if (key == 27 || key == 127)
			arrow_or_delete(key, line);
		else if (key == 4)
		{
			if (control_d(line))
				break ;
		}
		else if (key != '\n' && ft_cinset(key, WHITESPACE))
			add_key(line, key);
		if (g_info.cur_in_history == 0 || key == '\n')
			bzero_and_cpy(cur, line);
	}
	return (0);
}

char	*read_everything(void)
{
	t_history	*cur;
	char		*line;
	char		key;

	key = 0;
	if (ft_calloc((void **)&line, LINE_MAX, sizeof(char)))
		return (NULL);
	cur = (t_history *)g_info.history_head->data;
	g_info.prompt_len += g_info.echo_padding;
	if (read_everything_suite(key, line, cur))
		return (NULL);
	if (g_info.echo_padding > 0)
		g_info.echo_padding = 0;
	return (line);
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

void	read_line(int first)
{
	char	**colon_split;
	char	*line;
	int		crashed;
	int		i;

	colon_split = NULL;
	i = 0;
	crashed = FALSE;
	if (first)
		g_info.history_head = ft_create_elem(create_history_struct());
	else
		ft_list_push_front(&g_info.history_head, create_history_struct());
	line = read_everything();
	remove_colons(line, 0);
	colon_split = ft_split(line, COLON);
	ft_printf("\n");
	do_colon_split(colon_split, i);
	secure_free(line);
	free_tab(&colon_split);
}
