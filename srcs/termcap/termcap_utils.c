/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:23:19 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/29 14:33:48 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		init_termcap()
{
	char *term;

	term = getenv("TERM");
	tgetent(NULL, term);
	tcgetattr(STDOUT_FILENO, &info.termios_p);
	info.termios_p.c_lflag &= ~(ICANON | ECHO);
    info.termios_p.c_cc[VTIME] = 0;
    info.termios_p.c_cc[VMIN] = 1;
	tcsetattr(STDOUT_FILENO, TCSANOW, &info.termios_p);

	info.cursor.col = tgetnum("co");
	info.cursor.lin = tgetnum("li");
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
}

int get_pos(int *x, int *y)
{
	char buf[30]={0};
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

	list_len = ft_list_size(info.history_head);
	if (!(cur = ft_list_at(info.history_head, info.cur_in_history + 1)))
		return ;
	if (info.cur_in_history < list_len)
		info.cur_in_history++;
	hist = (t_history *)cur->data;
	tputs(tgoto(tgetstr("cm", NULL), info.cursor.start_posx, info.cursor.posy), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	tputs(hist->line, 1, ft_putchar);
	info.cursor.posx = info.cursor.start_posx + ft_strlen(hist->line);
	ft_bzero(line, ft_strlen(line));
	ft_strcpy(line, hist->line);
}

void		print_prev_cmd(char *line)
{
	t_list *cur;
	t_history *hist;

	if (!(cur = ft_list_at(info.history_head, info.cur_in_history - 1)))
		return ;
	if (info.cur_in_history > 0)
		info.cur_in_history--;
	hist = (t_history *)cur->data;
	tputs(tgoto(tgetstr("cm", NULL), info.cursor.start_posx, info.cursor.posy), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	tputs(hist->line, 1, ft_putchar);
	info.cursor.posx = info.cursor.start_posx + ft_strlen(hist->line);
	ft_bzero(line, ft_strlen(line));
	ft_strcpy(line, hist->line);
}

void		check_for_arrows(char *line)
{
	char	key;
	int		cursor;

	cursor = info.cursor.posx - info.prompt_len + 1;
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
			info.cursor.posx += cursor < ft_strlen(line) ? 1 : 0; // RIGHT KEY
		if (key == 68)
			info.cursor.posx -= cursor > 0 ? 1 : 0; // LEFT KEY
		tputs(tgoto(tgetstr("cm", NULL), info.cursor.posx, info.cursor.posy), 1, ft_putchar);
	}
}
