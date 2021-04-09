/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:17:51 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/09 18:10:29 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		add_char(char *dest, char key, int index)
{
	char	*tmp_one;
	char	*tmp_two;

	tmp_one = ft_substr(dest, 0, index);
	tmp_two = ft_substr(dest, index, ft_strlen(dest));
	ft_bzero(dest, ft_strlen(dest));
	ft_strcpy(dest, tmp_one);
	ft_strncat(dest, &key, 1);
	ft_strncat(dest, tmp_two, ft_strlen(tmp_two));
	free(tmp_one);
	free(tmp_two);
}

void		remove_char(char *line, int index)
{
	while (line[index])
	{
		line[index] = line[index + 1];
		index++;
	}
}

void		add_key(char *dest, char key)
{

	int		cursor;

	cursor = g_info.cursor.posx - g_info.prompt_len + 1;
	add_char(dest, key, cursor);
	tputs(tgoto(tgetstr("cm", NULL), g_info.cursor.start_posx, g_info.cursor.posy), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	ft_putstr_fd(dest, 1);
	tputs(tgoto(tgetstr("cm", NULL), g_info.cursor.posx + 1, g_info.cursor.posy), 1, ft_putchar);
}

void		delete_key(char *dest)
{
	int		i;
	int		cursor;

	i = 0;
	cursor = g_info.cursor.posx - g_info.prompt_len + 1;
	if (g_info.cursor.posx >=	 g_info.prompt_len)
	{
		while(dest[i] && i < cursor)
			i++;
		if (dest && dest[i - 1])
			i--;
		remove_char(dest, i);
		if (g_info.cursor.posx >= g_info.prompt_len)
			g_info.cursor.posx--;
		tputs(tgoto(tgetstr("cm", NULL), g_info.cursor.posx, g_info.cursor.posy), 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
	}
}

int			control_d(char *line)
{
	int		cursor;

	cursor = g_info.cursor.posx - g_info.prompt_len + 1;
	if (line && line[cursor])
	{
		remove_char(line, cursor);
		tputs(tgoto(tgetstr("cm", NULL), g_info.cursor.posx, g_info.cursor.posy), 1, ft_putchar);
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

// g_info.cursor.posx - g_info.prompt_len + 1 : this formula lets me checkout where cursor is on string
// may be useful to insert or delete characters

char 	*read_everything()
{
	t_history	*cur;
	char		*line;
	char		key;

	key = 0;
	if (ft_calloc((void **)&line, LINE_MAX, sizeof(char)))
		return (NULL);
	cur = (t_history *)g_info.history_head->data;
	g_info.prompt_len += g_info.echo_padding;
	while (key != '\n')
	{
		get_pos(&g_info.cursor.posx, &g_info.cursor.posy);
		if (read(STDIN_FILENO, &key, 1) == -1)
			return (NULL);
		if (g_info.kill)
		{
			g_info.kill = FALSE;
			ft_bzero(line, ft_strlen(line));
			ft_bzero(cur->line, ft_strlen(cur->line));
		}
		if (key == 27)
			check_for_arrows(line);
		else if (key == 127)
			delete_key(line);
		else if (key == 4)
		{
			if (control_d(line))
				break;
		}
		else if (key != '\n' && ft_cinset(key, WHITESPACE))
			add_key(line, key);
		if (g_info.cur_in_history == 0 || key == '\n')
		{
			ft_bzero(cur->line, ft_strlen(cur->line));
			ft_strcpy(cur->line, line);
		}
	}
	if (g_info.echo_padding > 0)
		g_info.echo_padding = 0;
	return (line);
}

int			ft_isalpha_ordollar(int c)
{
	if (c == '?' || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

// bslashes within a dquote only work if the following character is a dollar, a dquote,(a backquote) or another bslash
// not sure whether backquotes should be supported or not 

// other warning : when used solo, a backslash lets you finish a command in line under current one. 
// should i implement this ?

int			dollar(char *line, int *index, int dquote)
{
	char	*var;
	t_list	*var_list;
	t_env	*var_key;
	int		i;
	(void)dquote;

	i = 0;
	if (!line[*index] || !line[*index + 1] || (line[*index + 1] && !ft_isalpha_ordollar(line[*index + 1])))
	{
		*index += 1;
		return (FAILURE);
	}
	if (ft_calloc((void **)&var, 256, sizeof(char)))
		return (FAILURE);
	while (line[*index] && (ft_isalpha(line[*index]) || (line[*index] == DOLLAR && i == 0) || (line[*index] == '?')))
	{
		if (i > 0)
			var[i - 1] = line[*index];
		remove_char(line, *index);
		i++;
	}
	if ((var_list = ft_list_find(g_info.env_head, create_env_struct(var, NULL), cmp_env)))
	{
		var_key = (t_env *)var_list->data;
		i = 0;
		while (var_key->value[i])
		{
			add_char(line, var_key->value[i], *index);
			*index += 1;
			i++;
		}
	}
	return (SUCCESS);
}

int			backslash(char *line, int *index, int dquote)
{
	if (!dquote)
	{
		remove_char(line, *index);
		*index += 1;
	}
	else if (dquote)
	{
		if (line[*index + 1] && (line[*index + 1] == BSLASH || line[*index + 1] == '$' ||
			line[*index + 1] == DQUOTE))
		{
			remove_char(line, *index);
			if (!line[*index + 1])
				return (FAILURE);
		}
		*index += 1;
	}
	return (SUCCESS);
}

int			count_exceptions(int quote, int dquote)
{
	if (quote % 2 != 0 || dquote % 2 != 0)
		return (1);
	else
		return (0);
}

int			transform_line(char *line, int index, int quote, int dquote)
{
	int		ret = 0;

	while (line[index] && line[index] != BSLASH && line[index] != QUOTE && \
		line[index] != DQUOTE && line[index] != DOLLAR)
		index++;
	if (line[index] == BSLASH)
		backslash(line, &index, 0);
	if (line[index] == DOLLAR)
		dollar(line, &index, 0);
	if (line[index] == QUOTE)
	{
		remove_char(line, index);
		ft_list_push_front(&g_info.block_head, create_block_struct(index, -1));
		while (line[index] && line[index] != QUOTE)
			index++;
		if (!line[index])
			quote += 1;
		else if (line[index] == QUOTE)
		{
			remove_char(line, index);
			((t_block *)g_info.block_head->data)->end = index;
		}
	}
	if (line[index] == DQUOTE)
	{
		remove_char(line, index);
		ft_list_push_front(&g_info.block_head, create_block_struct(index, -1));
		while (line[index] && line[index] != DQUOTE)
		{
			if (line[index] == BSLASH)
			{
				if (backslash(line, &index, 1))
					return (FAILURE);
			}
			else if (line[index] == DOLLAR)
				dollar(line, &index, 1);
			else
				index++;
		}
		if (!line[index])
			dquote += 1;
		else if (line[index] == DQUOTE)
		{
			remove_char(line, index);
			((t_block *)g_info.block_head->data)->end = index;
		}
	}
	if (line[index])
		ret = transform_line(line, index, quote, dquote);
	else
		ret = count_exceptions(quote, dquote);
	return (ret);
}

int			is_there_colon_in_line(char *line)
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
** i might modify our line in this function, as in removing any unnecessary backslashes,
** quotes, double quotes etc..
** the point is to process our line so that it is readable by our read_cmd function
*/

// currently building a way to know if blocks exist
// colons won't work right now BECUASE OF THE SPLIT

void		read_line(int first)
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
			ft_printf("\nminisheh: parsing error: number of quotes should be even\n");
			break;
		}
		read_cmd(colon_split[i], 0, 0);
		i++;
	}
	if (line)
		free(line);
	line = NULL;
	free_tab(&colon_split);
}
