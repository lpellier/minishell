/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_and_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:31:03 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/05 17:44:15 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*sublint(int *src, int index)
{
	int		i;
	int		*cpy;

	if (ft_calloc((void **)&cpy, LINE_MAX, sizeof(int)))
		return (NULL);
	bzero_lint(cpy, LINE_MAX);
	i = 0;
	while (src[index] != -1)
	{
		cpy[i] = src[index];
		index++;
		i++;
	}
	return (cpy);
}

void	add_key(t_info *info, char *dest, char key)
{
	int		cursor;

	cursor = (info->cursor.posx - info->terminfo.prompt_len) + \
		(info->cursor.posy * info->terminfo.col);
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
	cursor = (info->cursor.posx - info->terminfo.prompt_len) + \
		(info->cursor.posy * info->terminfo.col);
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
