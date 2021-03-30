/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:17:51 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/30 17:08:11 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		add_key(char *dest, char key)
{
	char	*tmp_one;
	char	*tmp_two;
	int		cursor;

	cursor = info.cursor.posx - info.prompt_len + 1;
	tmp_one = ft_substr(dest, 0, cursor);
	tmp_two = ft_substr(dest, cursor, ft_strlen(dest));
	ft_bzero(dest, LINE_MAX);
	ft_strcpy(dest, tmp_one);
	ft_strncat(dest, &key, 1);
	ft_strncat(dest, tmp_two, ft_strlen(tmp_two));
	free(tmp_one);
	free(tmp_two);
	tputs(tgoto(tgetstr("cm", NULL), info.cursor.start_posx, info.cursor.posy), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	ft_putstr_fd(dest, 1);
	tputs(tgoto(tgetstr("cm", NULL), info.cursor.posx + 1, info.cursor.posy), 1, ft_putchar);
}

void		delete_key(char *dest)
{
	int		i;
	int		cursor;

	i = 0;
	cursor = info.cursor.posx - info.prompt_len + 1;
	while(dest[i] && i < cursor)
		i++;
	if (dest && dest[i - 1])
		i--;
	while (dest[i])
	{
		dest[i] = dest[i + 1];
		i++;
	}
	if (info.cursor.posx >= info.prompt_len)
		info.cursor.posx--;
	tputs(tgoto(tgetstr("cm", NULL), info.cursor.posx, info.cursor.posy), 1, ft_putchar);
	tputs(tgetstr("dc", NULL), 1, ft_putchar);
}

// info.cursor.posx - info.prompt_len + 1 : this formula lets me checkout where cursor is on string
// may be useful to insert or delete characters

char 	*read_everything()
{
	t_history	*cur;
	char		*line;
	char		key;

	key = 0;
	line = ft_calloc(LINE_MAX, sizeof(char));
	cur = (t_history *)info.history_head->data;
	while (key != '\n')
	{
		get_pos(&info.cursor.posx, &info.cursor.posy);
		if (read(0, &key, 1) == -1)
			return (NULL);
		if (key == 27)
			check_for_arrows(line);
		else if (key == 127)
			delete_key(line);
		else if (key != '\n')
			add_key(line, key);
		if (info.cur_in_history == 0 || key == '\n')
		{
			ft_bzero(cur->line, ft_strlen(cur->line));
			ft_strcpy(cur->line, line);
		}
	}
	return (line);
}

/* 
** reads line using gnl and feeds t_cmd linked lists 
** i might modify our line in this function, as in removing any unnecessary backslashes,
** quotes, double quotes etc..
** the point is to process our line so that it is readable by our read_cmd function
*/

void		read_line(int first)
{
	char *line;

	if (first)
		info.history_head = ft_create_elem(create_history_struct());
	else
    	ft_list_push_front(&info.history_head, create_history_struct());
	line = read_everything();
	check_sep(line);
	read_cmd(line, 0, 0);
	if (line)
		free(line);
	line = NULL;
	if (info.output)
	{
		ft_printf("%s", info.output);
		free(info.output);
	}
	info.output = NULL;
}
