/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:17:51 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/08 16:34:08 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_char(char *dest, char key, int index)
{
	char	*tmp_one;
	char	*tmp_two;

	tmp_one = ft_substr(dest, 0, index);
	tmp_two = ft_substr(dest, index, ft_strlen(dest));
	ft_bzero(dest, ft_strlen(dest));
	ft_strcpy(dest, tmp_one);
	ft_strncat(dest, &key, 1);
	ft_strncat(dest, tmp_two, ft_strlen(tmp_two));
	free(tmp_one);
	free(tmp_two);
}

void	remove_char(char *line, int index)
{
	while (line[index])
	{
		line[index] = line[index + 1];
		index++;
	}
}

void	add_key(char *dest, char key)
{
	int		cursor;

	cursor = g_info.cursor.posx - g_info.prompt_len + 1;
	add_char(dest, key, cursor);
	tputs(tgoto(tgetstr("cm", NULL), g_info.cursor.start_posx, \
		g_info.cursor.posy), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	ft_putstr_fd(dest, 1);
	tputs(tgoto(tgetstr("cm", NULL), g_info.cursor.posx + 1, \
		g_info.cursor.posy), 1, ft_putchar);
}

void	delete_key(char *dest)
{
	int		i;
	int		cursor;

	i = 0;
	cursor = g_info.cursor.posx - g_info.prompt_len + 1;
	if (g_info.cursor.posx >= g_info.prompt_len)
	{
		while (dest[i] && i < cursor)
			i++;
		if (dest && dest[i - 1])
			i--;
		remove_char(dest, i);
		if (g_info.cursor.posx >= g_info.prompt_len)
			g_info.cursor.posx--;
		tputs(tgoto(tgetstr("cm", NULL), g_info.cursor.posx, \
			g_info.cursor.posy), 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
	}
}

// g_info.cursor.posx - g_info.prompt_len + 1 : this formula 
//		lets me checkout where cursor is on string
// may be useful to insert or delete characters

char 	*read_everything(void)
{
	t_history	*cur;
	char		*line;
	char		key;

	key = 0;
	if (ft_calloc((void **)&line, LINE_MAX, sizeof(char)))
		return (NULL);
	cur = (t_history *)g_info.history_head->data;
	g_info.prompt_len += g_info.echo_padding;
	while (key != '\n')
	{
		get_pos(&g_info.cursor.posx, &g_info.cursor.posy);
		if (read(0, &key, 1) == -1)
			return (NULL);
		if (key == 27)
			check_for_arrows(line);
		else if (key == 127)
			delete_key(line);
		else if (key == 4)
		{
			if (control_d(line))
				break ;
		}
		else if (key != '\n')
			add_key(line, key);
		if (g_info.cur_in_history == 0 || key == '\n')
		{
			ft_bzero(cur->line, ft_strlen(cur->line));
			ft_strcpy(cur->line, line);
		}
	}
	if (g_info.echo_padding > 0)
		g_info.echo_padding = 0;
	return (line);
}
