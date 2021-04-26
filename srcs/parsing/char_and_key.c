/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_and_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:31:03 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/26 10:41:25 by lpellier         ###   ########.fr       */
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
	secure_free(tmp_one);
	secure_free(tmp_two);
}

void	remove_char(char *line, int index)
{
	while (line[index])
	{
		line[index] = line[index + 1];
		index++;
	}
}

void	move_right(char *dest)
{
	if (g_info->cursor.posy * tgetnum("co") + g_info->cursor.posx < (ft_strlen(dest) + g_info->prompt_len))
	{
		(g_info->cursor.posx)++;
		if (g_info->cursor.posx >= tgetnum("co"))
		{
			(g_info->cursor.posy)++;
			g_info->cursor.posx = 0;
			tputs(tgetstr("do", NULL), 1, ft_putchar);
		}
	}
	tputs(tgoto(tgetstr("ch", NULL), 1, g_info->cursor.posx), 1, ft_putchar);
}

void	move_left()
{
	g_info->cursor.posx -= 1;
	if (g_info->cursor.posy)
	{
		if (g_info->cursor.posx < 0)
		{
			(g_info->cursor.posx) = tgetnum("co") - 1;
			(g_info->cursor.posy)--;
			tputs(tgetstr("up", NULL), 1, ft_putchar);
		}
	}
	else if (g_info->cursor.posx < g_info->prompt_len)
			(g_info->cursor.posx)++;
	tputs(tgoto(tgetstr("ch", NULL), 1, g_info->cursor.posx), 1, ft_putchar);
}

void	add_key(char *dest, char key)
{
	int		cursor;
	int		count;

	cursor = g_info->cursor.posx + g_info->cursor.posy * g_info->cursor.col - g_info->prompt_len;
	add_char(dest, key, cursor);
	tputs(tgoto(tgetstr("ch", NULL), 1, g_info->prompt_len), 1, ft_putchar);
	count = g_info->cursor.posy;
	while (count-- > 0)
		tputs(tgetstr("up", NULL), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	ft_putstr_fd(dest, STDOUT_FILENO);
	move_right(dest);
	// tputs(tgoto(tgetstr("ch", NULL), 1, g_info->cursor.posx), 1, ft_putchar);
}

void	delete_key(char *dest)
{
	int		i;
	int		cursor;

	i = 0;
	cursor = g_info->cursor.posx + g_info->cursor.posy * g_info->cursor.col - g_info->prompt_len;
	if (g_info->cursor.posx >= g_info->prompt_len || g_info->cursor.posy > 0)
	{
		while (dest[i] && i < cursor)
			i++;
		if (dest && dest[i - 1])
			i--;
		remove_char(dest, i);
		move_left();
		// tputs(tgoto(tgetstr("ch", NULL), 1, g_info->cursor.posx), 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
	}
}
