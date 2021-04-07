/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:17:51 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/07 15:40:19 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_char(char *dest, char key, int index)
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

void	remove_char(char *line, int index)
{
	while (line[index])
	{
		line[index] = line[index + 1];
		index++;
	}
}

void	add_key(char *dest, char key)
{
	int		cursor;

	cursor = g_info.cursor.posx - g_info.prompt_len + 1;
	add_char(dest, key, cursor);
	tputs(tgoto(tgetstr("cm", NULL), g_info.cursor.start_posx, \
		g_info.cursor.posy), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	ft_putstr_fd(dest, 1);
	tputs(tgoto(tgetstr("cm", NULL), g_info.cursor.posx + 1, \
		g_info.cursor.posy), 1, ft_putchar);
}

void	delete_key(char *dest)
{
	int		i;
	int		cursor;

	i = 0;
	cursor = g_info.cursor.posx - g_info.prompt_len + 1;
	while (dest[i] && i < cursor)
		i++;
	if (dest && dest[i - 1])
		i--;
	while (dest[i])
	{
		dest[i] = dest[i + 1];
		i++;
	}
	if (g_info.cursor.posx >= g_info.prompt_len)
		g_info.cursor.posx--;
	tputs(tgoto(tgetstr("cm", NULL), g_info.cursor.posx, \
		g_info.cursor.posy), 1, ft_putchar);
	tputs(tgetstr("dc", NULL), 1, ft_putchar);
}

/*
** info.cursor.posx - info.prompt_len + 1 : \
** this formula lets me checkout where cursor is on string
** may be useful to insert or delete characters
*/

char	*read_everything()
{
	t_history	*cur;
	char		*line;
	char		key;

	key = 0;
	if (ft_calloc((void **)&line, LINE_MAX, sizeof(char)))
		return (NULL);
	cur = (t_history *)g_info.history_head->data;
	while (key != '\n')
	{
		get_pos(&g_info.cursor.posx, &g_info.cursor.posy);
		if (read(0, &key, 1) == -1)
			return (NULL);
		if (key == 27)
			check_for_arrows(line);
		else if (key == 127)
			delete_key(line);
		else if (key == 4)
			add_key(line, 'd'); // ctrl D
		else if (key != '\n')
			add_key(line, key);
		if (g_info.cur_in_history == 0 || key == '\n')
		{
			ft_bzero(cur->line, ft_strlen(cur->line));
			ft_strcpy(cur->line, line);
		}
	}
	return (line);
}

/*
** bslashes within a dquote only work if the following character is a dollar, 
**		a dquote,(a backquote) or another bslash
** not sure whether backquotes should be supported or not 
*/

/*
** other warning : when used solo, a backslash lets you finish a 
**		command in line under current one. 
** should i implement this ?
*/

int	dollar(char *line, int *index, int dquote)
{
	char	*var;
	t_list	*var_list;
	t_env	*var_key;
	int		i;

	i = 0;
	if (ft_calloc((void **)&var, 256, sizeof(char)))
		return (FAILURE);
	while (line[*index] && (ft_isalpha(line[*index]) || line[*index] == DOLLAR))
	{
		if (i > 0)
			var[i - 1] = line[*index];
		remove_char(line, *index);
		i++;
	}
	if ((var_list = ft_list_find(g_info.env_head, \
		create_env_struct(var, NULL), cmp_env)))
	{
		var_key = (t_env *)var_list->data;
		i = 0;
		while (var_key->value[i])
		{
			add_char(line, var_key->value[i], *index);
			*index += 1;
			i++;
		}
		if (dquote)
			*index -= 1;
	}
	return (0);
}

int	backslash(char *line, int *index, int dquote)
{
	if (!dquote)
	{
		remove_char(line, *index);
		*index += 1;
	}
	else if (dquote)
	{
		if (line[*index + 1] && (line[*index + 1] == BSLASH || \
			line[*index + 1] == '$' || line[*index + 1] == DQUOTE))
		{
			remove_char(line, *index);
			if (!line[*index + 1])
				return (1);
		}
	}
	return (0);
}

void	transform_line(char *line, int index)
{
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
		while (line[index] != QUOTE)
			index++;
		remove_char(line, index);
	}
	if (line[index] == DQUOTE)
	{
		remove_char(line, index);
		while (line[index] != DQUOTE)
		{
			if (line[index] == BSLASH)
				if (backslash(line, &index, 1))
					return ;
			if (line[index] == DOLLAR)
				dollar(line, &index, 1);
			index++;
		}
		remove_char(line, index);
	}
	if (line[index])
		transform_line(line, index);
}

/*
** this function will return a false error when there 
**		will be a dquote precedeed by a bslash
** be wary of this
*/

int	count_exceptions(char *line)
{
	int	i;
	int	bslash;
	int	quote;
	int	dquote;

	i = 0;
	bslash = 0;
	quote = 0;
	dquote = 0;
	while (line[i])
	{
		if (line[i] == QUOTE)
			dquote++;
		else if (line[i] == DQUOTE)
			quote++;
		else if (line[i] == BSLASH)
			bslash++;
		i++;
	}
	if (quote % 2 != 0 || dquote % 2 != 0)
		return (1);
	else
		return (0);
}

/* 
** reads line using gnl and feeds t_cmd linked lists 
** i might modify our line in this function, as in 
**		removing any unnecessary backslashes,
** quotes, double quotes etc..
** the point is to process our line so that it is readable 
**		by our read_cmd function
*/

void	read_line(int first)
{
	char	*line;

	if (first)
		g_info.history_head = ft_create_elem(create_history_struct());
	else
		ft_list_push_front(&g_info.history_head, create_history_struct());
	line = read_everything();
	transform_line(line, 0);
	if (count_exceptions(line))
	{
		free(line);
		ft_printf("\nminisheh: parsing error: number of quotes should be even\n");
		return ;
	}
	ft_printf("\n");
	read_cmd(line, 0, 0);
	if (line)
		free(line);
	line = NULL;
}
