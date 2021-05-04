/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_and_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:31:03 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/04 17:02:56 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	intcat(int *dest, int start, int *src)
{
	int		i;

	i = 0;
	while (src[i] != - 1)
	{
		dest[start] = src[i];
		i++;
		start++;
	}
}

int		*sublint(int *src, int index)
{
	int		i;
	int 	*cpy;

	if (ft_calloc((void **)&cpy, LINE_MAX, sizeof(int)))
		return (NULL);
	bzero_lint(cpy, LINE_MAX);
	i = 0;
	while (src[index] != - 1)
	{
		cpy[i] = src[index];
		index++;
		i++;
	}
	return (cpy);
}

void	add_int(int *dest, int key, int index)
{
	int		*tmp;

	tmp = sublint(dest, index);
	dest[index] = key;
	index++;
	intcat(dest, index, tmp);
	secure_free(tmp);
}

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

void	remove_int(int	*lint, int index)
{
	while (lint[index] != -1)
	{
		lint[index] = lint[index + 1];
		index++;
	}
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
		if (info->cursor.posx < 0)
		{
			info->cursor.posx = info->terminfo.col - 1;
			info->cursor.posy -= 1;
			tputs(tgetstr("up", NULL), 1, ft_putchar);
		}
	}
	else if (info->cursor.posx < info->terminfo.prompt_len)
			info->cursor.posx += 1;
	tputs(tgoto(tgetstr("ch", NULL), 1, info->cursor.posx), 1, ft_putchar);
}

void	add_key(t_info *info, char *dest, char key)
{
	int		cursor;

	cursor = (info->cursor.posx - info->terminfo.prompt_len) + (info->cursor.posy * info->terminfo.col);
	add_char(dest, key, cursor);
	move_right(info, dest);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	clear_line(info);
	ft_putstr_fd(dest, STDOUT_FILENO);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
}

void	delete_key(t_info *info, char *dest)
{
	int		i;
	int		j;
	int		count;
	int		cursor;

	i = 0;
	count = 0;
	cursor = (info->cursor.posx - info->terminfo.prompt_len) + (info->cursor.posy * info->terminfo.col);
	if (info->cursor.posx > info->terminfo.prompt_len || info->cursor.posy > 0)
	{
		while (dest[i] && i < cursor)
			i++;
		if (dest && dest[i - 1])
			i--;
		remove_char(dest, i);
		move_left(info);
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
		j = info->terminfo.prompt_len + ft_strlen(dest);
		while (j >= info->terminfo.col && info->cursor.posy != count + 1)
		{
			count += 1;
			tputs(tgetstr("do", NULL), 1, ft_putchar);
			j -= info->terminfo.col;
		}
		info->cursor.posy += count;
		clear_line(info);
		info->cursor.posy -= count;
		ft_putstr_fd(dest, STDOUT_FILENO);
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
	}
}
