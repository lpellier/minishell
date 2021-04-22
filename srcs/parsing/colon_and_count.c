/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colon_and_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:13:27 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/22 16:25:39 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_exceptions(int quote, int dquote)
{
	if (quote % 2 != 0 || dquote % 2 != 0)
		return (1);
	else
		return (0);
}

int	is_there_colon_in_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == COLON)
			return (1);
		i++;
	}
	return (0);
}

void	remove_colons(char *line, int i)
{
	while (line[i] && line[i] != QUOTE && line[i] != DQUOTE)
		i++;
	if (line[i] == QUOTE)
	{
		while (line[i] && line[i] != QUOTE)
		{
			if (line[i] == COLON)
				remove_char(line, i);
			else
				i++;
		}
	}
	if (line[i] == DQUOTE)
	{
		while (line[i] && line[i] != DQUOTE)
		{
			if (line[i] == COLON)
				remove_char(line, i);
			else
				i++;
		}
	}
	if (line[i])
		remove_colons(line, i + 1);
}

void	do_colon_split(char	**colon_split, int i)
{
	while (colon_split && colon_split[i])
	{
		if (transform_line(colon_split[i], 0, 0, 0))
		{
			g_info->cmd_status = 1;
			ft_printf("minisheh: parsing error: number of quotes ");
			ft_printf("should be even\n");
			break ;
		}
		read_cmd(colon_split[i], 0, 0);
		i++;
	}
}
