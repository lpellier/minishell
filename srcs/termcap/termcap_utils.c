/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:23:19 by lpellier          #+#    #+#             */
/*   Updated: 2021/05/05 16:19:37 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	restore_term(t_info *info)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &info->saved_term);
}

void	clear_line(t_info *info)
{
	int		count;

	count = info->cursor.posy;
	while (count > 0)
	{
		tputs(tgetstr("cr", NULL), 1, ft_putchar);
		tputs(tgetstr("ce", NULL), 1, ft_putchar);
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		count--;
	}
	tputs(tgoto(tgetstr("ch", NULL), 1, \
		info->terminfo.prompt_len), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
}

void	print_last_cmd(t_info *info, char *line)
{
	t_list		*cur;
	t_history	*hist;
	int			list_len;

	list_len = ft_list_size(info->history_head);
	cur = ft_list_at(info->history_head, info->cur_in_history + 1);
	if (!(cur))
		return ;
	if (info->cur_in_history < list_len)
		info->cur_in_history++;
	hist = (t_history *)cur->data;
	clear_line(info);
	info->cursor.posy = hist->posy;
	info->cursor.posx = (ft_strlen(hist->line) + \
		info->terminfo.prompt_len) % info->terminfo.col;
	ft_putstr_fd(hist->line, STDOUT_FILENO);
	ft_bzero(line, ft_strlen(line));
	ft_strcpy(line, hist->line);
}

void	print_prev_cmd(t_info *info, char *line)
{
	t_list		*cur;
	t_history	*hist;

	cur = ft_list_at(info->history_head, info->cur_in_history - 1);
	if (!(cur))
		return ;
	if (info->cur_in_history > 0)
		info->cur_in_history--;
	hist = (t_history *)cur->data;
	clear_line(info);
	info->cursor.posy = hist->posy;
	info->cursor.posx = (ft_strlen(hist->line) + \
		info->terminfo.prompt_len) % info->terminfo.col;
	ft_putstr_fd(hist->line, STDOUT_FILENO);
	ft_bzero(line, ft_strlen(line));
	ft_strcpy(line, hist->line);
}

// 65 = UP KEY
// 66 = DOWN KEY
// 67 = RIGHT KEY
// 68 = LEFT KEY

void	check_for_arrows(t_info *info, char *line)
{
	char	key;
	int		cursor;

	cursor = info->cursor.posx + info->cursor.posy * \
		info->terminfo.col - info->terminfo.prompt_len;
	if (read(0, &key, 1) == -1)
		return ;
	if (key == 91)
	{
		if (read(0, &key, 1) == -1)
			return ;
		if (key == 65)
			print_last_cmd(info, line);
		if (key == 66)
			print_prev_cmd(info, line);
		if (key == 67)
			move_right(info, line);
		if (key == 68)
			move_left(info);
	}
}
