/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_everything1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:44:29 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/08 17:15:25 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	transform_line(char *line, int index, int quote_nb, int dquote_nb)
{
	int		ret;

	ret = 0;
	while (line[index] && line[index] != BSLASH && line[index] != QUOTE && \
		line[index] != DQUOTE && line[index] != DOLLAR)
		index++;
	if (line[index] == BSLASH)
		backslash(line, &index, 0);
	if (line[index] == DOLLAR)
		dollar(line, &index);
	if (line[index] == QUOTE)
		quote_nb += quote(line, &index);
	if (line[index] == DQUOTE)
		dquote_nb += dquote(line, &index);
	if (line[index])
		ret = transform_line(line, index, quote_nb, dquote_nb);
	else
		ret = count_exceptions(quote_nb, dquote_nb);
	return (ret);
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

/* 
** reads line using gnl and feeds t_cmd linked lists 
** i might modify our line in this function, as in removing any 
** unnecessary backslashes, quotes, double quotes etc..
** the point is to process our line so that it is readable by our 
** read_cmd function
*/

// currently building a way to know if blocks exist
// colons won't work right now BECUASE OF THE SPLIT

void	read_line(int first)
{
	char	**colon_split;
	char	*line;
	int		crashed;
	int		i;

	colon_split = NULL;
	i = 0;
	crashed = FALSE;
	if (first)
		g_info.history_head = ft_create_elem(create_history_struct());
	else
		ft_list_push_front(&g_info.history_head, create_history_struct());
	line = read_everything();
	colon_split = ft_split(line, COLON);
	ft_printf("\n");
	while (colon_split && colon_split[i])
	{
		if (transform_line(colon_split[i], 0, 0, 0))
		{
			g_info.cmd_status = 1;
			ft_printf("\nminisheh: parsing error: number of quotes");
			ft_printf(" should be even\n");
			break ;
		}
		read_cmd(colon_split[i], 0, 0);
		i++;
	}
	secure_free(line);
	free_tab(&colon_split);
}

int	control_d(char *line)
{
	int		cursor;

	cursor = g_info.cursor.posx - g_info.prompt_len + 1;
	if (line && line[cursor])
	{
		remove_char(line, cursor);
		tputs(tgoto(tgetstr("cm", NULL), g_info.cursor.posx, \
			g_info.cursor.posy), 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
	}
	else if (!line || !line[0])
	{
		ft_printf("exit");
		g_info.crashed = TRUE;
		return (FAILURE);
	}
	return (SUCCESS);
}
