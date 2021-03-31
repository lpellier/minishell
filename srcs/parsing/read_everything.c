/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:17:51 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/30 21:13:28 by lpellier         ###   ########.fr       */
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
		else if (key == 4)
			add_key(line, 'd'); // ctrl D
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

void		remove_char(char *line, int index)
{
	while (line[index])
	{
		line[index] = line[index + 1];
		index++;
	}
}

// bslashes within a dquote only work if the following character is a dollar, a dquote,(a backquote) or another bslash
// not sure whether backquotes should be supported or not 

// other warning : when used solo, a backslash lets you finish a command in line under current one. 
// should i implement this ?

int			backslash(char *line, int *index, int dquote)
{
	if (!dquote)
	{
		remove_char(line, *index);
		*index += 1;
	}
	else if (dquote)
	{
		if (line[*index + 1] && (line[*index + 1] == BSLASH || line[*index + 1] == '$' ||
			line[*index + 1] == DQUOTE))
		{
			remove_char(line, *index);
			if (!line[*index + 1])
				return (1);
		}
	}
	return (0);
}

void		transform_line(char *line, int index)
{
	while (line[index] && line[index] != BSLASH && line[index] != QUOTE && line[index] != DQUOTE)
		index++;
	if (line[index] == BSLASH)
		backslash(line, &index, 0);
	while (line[index] && line[index] != BSLASH && line[index] != QUOTE && line[index] != DQUOTE)
		index++;
	if (line[index] == QUOTE)
	{
		remove_char(line, index);
		while (line[index] != QUOTE)
			index++;
		remove_char(line, index);
	}
	if (line[index] == DQUOTE)
	{
		remove_char(line, index);
		while (line[index] != DQUOTE)
		{
			if (line[index] == BSLASH)
				if (backslash(line, &index, 1))
					return ;
			index++;
		}
		remove_char(line, index);
	}
	if (line[index])
		transform_line(line, index);
}

// this function will return a false error when there will be a dquote precedeed by a bslash
// be wary of this

int			count_exceptions(char *line)
{
	int		i;
	int		bslash, quote, dquote;

	i = 0;
	bslash = 0;
	quote = 0;
	dquote = 0;
	while (line[i])
	{
		if (line[i] == QUOTE)
			dquote++;
		else if (line[i] == DQUOTE)
			quote++;
		else if (line[i] == BSLASH)
			bslash++;
		i++;
	}
	if (quote % 2 != 0 || dquote % 2 != 0)
		return (1);
	else
		return (0);
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
	transform_line(line, 0);
	if (count_exceptions(line))
	{
		free(line);
		ft_printf("\nminisheh: parsing error: number of quotes should be even\n");
		return ;
	}
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
