/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 17:43:45 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/22 13:51:10 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	move_right(t_info *info, char *dest)
{
	if (info->cursor.posy * info->terminfo.col + info->cursor.posx \
		< (ft_strlen(dest) + info->terminfo.prompt_len))
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
