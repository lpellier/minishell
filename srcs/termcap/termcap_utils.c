/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:23:19 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/24 17:20:33 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	restore_term(void)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &g_info->saved_term);
}

void	clear_line(char *line)
{
	int		count;

	(void)line;
	count = g_info->cursor.posy;
	while (count > 0)
	{
		tputs(tgetstr("cr", NULL), 1, ft_putchar);
		tputs(tgetstr("ce", NULL), 1, ft_putchar);
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		count--;
	}
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
	count = 0;
	g_info->cursor.posx = 0;
	while (count < g_info->prompt_len)
	{
		g_info->cursor.posx += 1;
		tputs(tgoto(tgetstr("ch", NULL), 1, g_info->cursor.posx), 1, ft_putchar);
		count++;
	}
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
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
	clear_line(line);
	g_info->cursor.posy = hist->posy;
	if (g_info->cursor.posy)
		g_info->cursor.posx = (ft_strlen(hist->line) + g_info->prompt_len) % g_info->cursor.col;
	else
		g_info->cursor.posx = ft_strlen(hist->line) + g_info->prompt_len;
	ft_putstr_fd(hist->line, STDOUT_FILENO);
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
	clear_line(line);
	g_info->cursor.posy = hist->posy;
	if (g_info->cursor.posy)
		g_info->cursor.posx = (ft_strlen(hist->line) + g_info->prompt_len) % g_info->cursor.col;
	else
		g_info->cursor.posx = ft_strlen(hist->line) + g_info->prompt_len;
	ft_putstr_fd(hist->line, STDOUT_FILENO);
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

	cursor = g_info->cursor.posx + g_info->cursor.posy * g_info->cursor.col - g_info->prompt_len;
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
			move_right(line);
		if (key == 68)
			move_left();
	}
}
