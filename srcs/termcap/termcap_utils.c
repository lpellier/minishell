/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:23:19 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/21 12:38:50 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		init_termcap()
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &g_info->termios_p);
}

void		restore_term()
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &g_info->saved_term);
}

int get_pos(int *x, int *y)
{
	char buf[30] = {0};
	int i;
	int pow;
	char ch;

	*x = 0;
	*y = 0;
	write(1, "\033[6n", 4);
	for( i = 0, ch = 0; ch != 'R'; i++ )
	{
		if (!read(0, &ch, 1))
			return (1);
		buf[i] = ch;
	}
	if (i < 2)
		return(1);
	for( i -= 2, pow = 1; buf[i] != ';'; i--, pow *= 10)
		*x = *x + ( buf[i] - '0' ) * pow;
	for( i-- , pow = 1; buf[i] != '['; i--, pow *= 10)
		*y = *y + ( buf[i] - '0' ) * pow;
	*x -= 1;
	*y -= 1;
	return 0;
}

void		print_last_cmd(char *line)
{
	t_list *cur;
	t_history *hist;
	int		list_len;

	list_len = ft_list_size(g_info->history_head);
	if (!(cur = ft_list_at(g_info->history_head, g_info->cur_in_history + 1)))
		return ;
	if (g_info->cur_in_history < list_len)
		g_info->cur_in_history++;
	hist = (t_history *)cur->data;
	tputs(tgoto(tgetstr("cm", NULL), g_info->cursor.start_posx, g_info->cursor.posy), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	tputs(hist->line, 1, ft_putchar);
	g_info->cursor.posx = g_info->cursor.start_posx + ft_strlen(hist->line);
	ft_bzero(line, ft_strlen(line));
	ft_strcpy(line, hist->line);
}

void		print_prev_cmd(char *line)
{
	t_list *cur;
	t_history *hist;

	if (!(cur = ft_list_at(g_info->history_head, g_info->cur_in_history - 1)))
		return ;
	if (g_info->cur_in_history > 0)
		g_info->cur_in_history--;
	hist = (t_history *)cur->data;
	tputs(tgoto(tgetstr("cm", NULL), g_info->cursor.start_posx, g_info->cursor.posy), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	tputs(hist->line, 1, ft_putchar);
	g_info->cursor.posx = g_info->cursor.start_posx + ft_strlen(hist->line);
	ft_bzero(line, ft_strlen(line));
	ft_strcpy(line, hist->line);
}

void		check_for_arrows(char *line)
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
		if (key == 65) //UP KEY
			print_last_cmd(line);
		if (key == 66)
			print_prev_cmd(line); // DOWN KEY
		if (key == 67)
			g_info->cursor.posx += cursor < ft_strlen(line) ? 1 : 0; // RIGHT KEY
		if (key == 68)
			g_info->cursor.posx -= cursor > 0 ? 1 : 0; // LEFT KEY
		tputs(tgoto(tgetstr("cm", NULL), g_info->cursor.posx, g_info->cursor.posy), 1, ft_putchar);
	}
}
