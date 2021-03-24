/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:23:19 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/24 16:25:17 by lpellier         ###   ########.fr       */
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
	// if (info.termios_p.c_lflag & ICANON)
	// 	ft_printf("Terminal is in canonical mode.n");
}

int get_pos()
{
	char buf[30]={0};
	int i;
	int pow;
	char ch;

	info.cursor.posx = 0;
	info.cursor.posy = 0;
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
		info.cursor.posx = info.cursor.posx + ( buf[i] - '0' ) * pow;
	for( i-- , pow = 1; buf[i] != '['; i--, pow *= 10)
		info.cursor.posy = info.cursor.posy + ( buf[i] - '0' ) * pow;
	info.cursor.posx--;
	info.cursor.posy--;
	return 0;
}

void		print_last_cmd()
{
	t_list *cur;
	t_history *hist;
	// int		size;

	// ft_printf("%d\n", info.cur_in_history);
	if (!(cur = ft_list_at(info.history_head, info.cur_in_history)))
		return ;
	hist = (t_history *)cur->data;
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	tputs(hist->line, 1, ft_putchar);
	info.cur_in_history++;
}

void		print_prev_cmd()
{
	t_list *cur;
	t_history *hist;

	if (info.cur_in_history < 0)
		info.cur_in_history = 0;
	if (!(cur = ft_list_at(info.history_head, info.cur_in_history)))
		return ;
	info.cur_in_history--;
	hist = (t_history *)cur->data;
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	tputs(hist->line, 1, ft_putchar);
}

void		check_for_arrows(int index)
{
	char	key;
	char	*cm;

	cm = tgetstr("cm", NULL);
	if (read(0, &key, 1) == -1)
		return ;
	if (key == 91)
	{
		if (read(0, &key, 1) == -1)
			return ;
		if (key == 65) //UP KEY
			print_last_cmd();
		if (key == 66)
			print_prev_cmd(); // DOWN KEY
		if (key == 67)
			info.cursor.posx += info.cursor.posx <= index ? 1 : 0; // RIGHT KEY
		if (key == 68)
			info.cursor.posx -= info.cursor.posx < info.prompt_len? 0 : 1; // LEFT KEY
		tputs(tgoto(cm, info.cursor.posx, info.cursor.posy), 1, ft_putchar);
	}
}

char	*delete_char(char *str, int index)
{
	char *res;

	if (info.cursor.posx >= info.prompt_len)
		info.cursor.posx--;
	tputs(tgoto(tgetstr("cm", NULL), info.cursor.posx, info.cursor.posy), 1, ft_putchar);
	tputs(tgetstr("dc", NULL), 1, ft_putchar);
	
	res = ft_strjoin(ft_substr(str, 0, index - 1), ft_substr(str, index + 1, ft_strlen(str) - index));
	return (res);
}
