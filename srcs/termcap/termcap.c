/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:56:12 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/21 16:57:13 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_termcap(void)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &g_info->termios_p);
}

void	use_pow(int i, char *buf, int *x, int *y)
{
	int	pow;

	i -= 2;
	pow = 1;
	while (buf[i] != ';')
	{
		*x = *x + (buf[i] - '0') * pow;
		i--;
		pow *= 10;
	}
	i--;
	pow = 1;
	while (buf[i] != '[')
	{
		*y = *y + (buf[i] - '0') * pow;
		i--;
		pow *= 10;
	}
	*x -= 1;
	*y -= 1;
}

int	get_pos(int *x, int *y)
{
	char	buf[30];
	int		i;
	char	ch;

	*x = 0;
	*y = 0;
	i = -1;
	ch = 0;
	while (++i < 30)
		buf[i] = 0;
	i = 0;
	write(1, "\033[6n", 4);
	while (ch != 'R')
	{
		if (!read(0, &ch, 1))
			return (1);
		buf[i] = ch;
		i++;
	}
	if (i < 2)
		return (1);
	use_pow(i, buf, x, y);
	return (0);
}
