/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:23:19 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/21 16:56:34 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	restore_term(void)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &g_info->saved_term);
}

void	print_last_cmd(char *line)
{
	t_list		*cur;
	t_history	*hist;
	int			list_len;

	list_len = ft_list_size(g_info->history_head);
	cur = ft_list_at(g_info->history_head, g_info->cur_in_history + 1);
	if (!(cur))
		return ;
	if (g_info->cur_in_history < list_len)
		g_info->cur_in_history++;
	hist = (t_history *)cur->data;
	tputs(tgoto(tgetstr("cm", NULL), g_info->cursor.start_posx, \
		g_info->cursor.posy), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	tputs(hist->line, 1, ft_putchar);
	g_info->cursor.posx = g_info->cursor.start_posx + ft_strlen(hist->line);
	ft_bzero(line, ft_strlen(line));
	ft_strcpy(line, hist->line);
}

void	print_prev_cmd(char *line)
{
	t_list		*cur;
	t_history	*hist;

	cur = ft_list_at(g_info->history_head, g_info->cur_in_history - 1);
	if (!(cur))
		return ;
	if (g_info->cur_in_history > 0)
		g_info->cur_in_history--;
	hist = (t_history *)cur->data;
	tputs(tgoto(tgetstr("cm", NULL), g_info->cursor.start_posx, \
		g_info->cursor.posy), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	tputs(hist->line, 1, ft_putchar);
	g_info->cursor.posx = g_info->cursor.start_posx + ft_strlen(hist->line);
	ft_bzero(line, ft_strlen(line));
	ft_strcpy(line, hist->line);
}

// 65 = UP KEY
// 66 = DOWN KEY
// 67 = RIGHT KEY
// 68 = LEFT KEY

void	check_for_arrows(char *line)
{
	char	key;
	int		cursor;

	cursor = g_info->cursor.posx - g_info->prompt_len + 1;
	if (read(0, &key, 1) == -1)
		return ;
	if (key == 91)
	{
		if (read(0, &key, 1) == -1)
			return ;
		if (key == 65)
			print_last_cmd(line);
		if (key == 66)
			print_prev_cmd(line);
		if (key == 67)
			if (cursor < ft_strlen(line))
				g_info->cursor.posx += 1;
		if (key == 68)
			if (cursor > 0)
				g_info->cursor.posx -= 1;
		tputs(tgoto(tgetstr("cm", NULL), g_info->cursor.posx, \
			g_info->cursor.posy), 1, ft_putchar);
	}
}
