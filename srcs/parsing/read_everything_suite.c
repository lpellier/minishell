/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_everything_suite.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:02:24 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/26 23:19:36 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	special_keys(t_info *info, char key)
{
	if (key == 27)
		check_for_arrows(info, info->line);
	else if (key == 127)
		delete_key(info, info->line);
}

void	bzero_and_cpy(t_history *cur, char *line)
{
	ft_bzero(cur->line, ft_strlen(cur->line));
	ft_strcpy(cur->line, line);
}

void	update_history(t_info *info, t_history *cur)
{
	ft_bzero(cur->line, ft_strlen(cur->line));
	cur->posx = info->cursor.posx;
	cur->posy = info->cursor.posy;
	ft_strcpy(cur->line, info->line);
}

int	pass_q_and_dq(char *line, int i)
{
	if (line[i] && line[i] == QUOTE)
	{
		i++;
		while (line[i] && line[i] != QUOTE)
			i++;
	}
	if (line[i] && line[i] == BSLASH)
		i += 2;
	if (line[i] && line[i] == DQUOTE)
	{
		i++;
		while (line[i] && line[i] != DQUOTE)
			i++;
	}
	return (i);
}

void	toggle(int *bo, int *index)
{
	if (*bo == FALSE)
		*bo = TRUE;
	else
		*bo = FALSE;
	*index += 1;
}
