/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_and_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:31:03 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/26 23:36:04 by lpellier         ###   ########.fr       */
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

void	move_right(t_info *info, char *dest)
{
	if (info->cursor.posy * info->terminfo.col + info->cursor.posx < (ft_strlen(dest) + info->terminfo.prompt_len))
	{
		(info->cursor.posx)++;
		if (info->cursor.posx >= info->terminfo.col)
		{
			(info->cursor.posy)++;
			info->cursor.posx = 0;
			tputs(tgetstr("do", NULL), 1, ft_putchar);
		}
	}
	tputs(tgoto(tgetstr("ch", NULL), 1, info->cursor.posx), 1, ft_putchar);
}

void	move_left(t_info *info)
{
	info->cursor.posx -= 1;
	if (info->cursor.posy)
	{
		if (info->cursor.posx <= 0)
		{
			info->cursor.posx = info->terminfo.col;
			info->cursor.posy -= 1;
			tputs(tgetstr("up", NULL), 1, ft_putchar);
		}
	}
	else if (info->cursor.posx < info->terminfo.prompt_len)
			info->cursor.posx += 1;
	tputs(tgoto(tgetstr("ch", NULL), 0, info->cursor.posx), 1, ft_putchar);
}

void	add_key(t_info *info, char *dest, char key)
{
	int		cursor;

	cursor = (info->cursor.posx - info->terminfo.prompt_len) + (info->cursor.posy * info->terminfo.col);
	clear_line(info);
	add_char(dest, key, cursor);
	ft_putstr_fd(dest, STDOUT_FILENO);
	move_right(info, dest);
}

void	delete_key(t_info *info, char *dest)
{
	int		i;
	int		cursor;

	i = 0;
	cursor = (info->cursor.posx - info->terminfo.prompt_len) + (info->cursor.posy * info->terminfo.col);
	if (info->cursor.posx > info->terminfo.prompt_len || info->cursor.posy > 0)
	{
		while (dest[i] && i < cursor)
			i++;
		if (dest && dest[i - 1])
			i--;
		clear_line(info);
		remove_char(dest, i);
		ft_putstr_fd(dest, STDOUT_FILENO);
		info->cursor.posx -= 1;
		if (info->cursor.posy)
		{
			if (info->cursor.posx <= 0)
			{
				info->cursor.posx = info->terminfo.col;
				info->cursor.posy -= 1;
			}
		}
		else if (info->cursor.posx < info->terminfo.prompt_len)
				info->cursor.posx += 1;
	}
}
