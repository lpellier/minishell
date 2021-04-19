/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:17:51 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/19 17:16:48 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	special_keys(char key)
{
	if (key == 27)
		check_for_arrows(g_info.line);
	else if (key == 127)
		delete_key(g_info.line);
}

void	bzero_and_cpy(t_history *cur, char *line)
{
	ft_bzero(cur->line, ft_strlen(cur->line));
	ft_strcpy(cur->line, line);
}

void	update_history(t_history *cur)
{
	ft_bzero(cur->line, ft_strlen(cur->line));
	ft_strcpy(cur->line, g_info.line);
}

// g_info.cursor.posx - g_info.prompt_len + 1 : this formula 
//     lets me checkout where cursor is on string
// may be useful to insert or delete characters

int	read_keys(char key, t_history *cur)
{
	while (key != '\n')
	{
		get_pos(&g_info.cursor.posx, &g_info.cursor.posy);
		if (read(STDIN_FILENO, &key, 1) == -1)
			return (FAILURE);
		if (g_info.kill)
		{
			g_info.kill = FALSE;
			ft_bzero(g_info.line, ft_strlen(g_info.line));
			ft_bzero(cur->line, ft_strlen(cur->line));
		}
		if (key == 27 || key == 127)
			special_keys(key);
		else if (key == 4)
		{
			if (control_d())
				break ;
		}
		else if (key != '\n' && ft_cinset(key, WHITESPACE))
			add_key(g_info.line, key);
		if (g_info.cur_in_history == 0 || key == '\n')
			update_history(cur);
	}
	return (SUCCESS);
}

int	read_line(void)
{
	t_history	*cur;
	char		key;

	key = 0;
	ft_bzero(g_info.line, ft_strlen(g_info.line));
	cur = (t_history *)g_info.history_head->data;
	g_info.prompt_len += g_info.echo_padding;
	if (read_keys(key, cur))
	{
		g_info.sig_status = 1;
		return (FAILURE);
	}
	if (g_info.echo_padding > 0)
		g_info.echo_padding = 0;
	return (SUCCESS);
}

// bslashes within a dquote only work if the following character is a 
//	dollar, a dquote,(a backquote) or another bslash
// not sure whether backquotes should be supported or not 

// other warning : when used solo, a backslash lets you finish a 
//	command in line under current one. 
// should i implement this ?

int	count_words_colon(char *line)
{
	int		i;
	int		count;

	count = 1;
	i = 0;
	while (line[i])
	{
		if (line[i] && line[i] == QUOTE)
		{
			i++;
			while (line[i] && line[i] != QUOTE)
				i++;
		}
		if (line[i] && line[i] == DQUOTE)
		{
			i++;
			while (line[i] && line[i] != DQUOTE)
				i++;
		}
		if (line[i] && line[i] == COLON)
			count++;
		i++;
	}
	return (count);
}

int	test(char *line, int i)
{
	if (line[i] && line[i] == QUOTE)
	{
		i++;
		while (line[i] && line[i] != QUOTE)
			i++;
	}
	if (line[i] && line[i] == DQUOTE)
	{
		i++;
		while (line[i] && line[i] != DQUOTE)
			i++;
	}
	return (i);
}

char	**ft_split_colon(char *line)
{
	int		i;
	int		old;
	int		count;
	int		words_len;
	char	**ret;

	i = 0;
	words_len = count_words_colon(line);
	old = 0;
	count = 0;
	ret = NULL;
	if (ft_calloc((void **)&ret, words_len + 1, sizeof(char *)))
		return (NULL);
	if (words_len == 1)
	{
		if (ft_calloc((void **)&ret[0], 4096, sizeof(char)))
			return (NULL);
		ft_strcpy(ret[0], line);
		return (ret);
	}
	while (line[i])
	{
		i = test(line, i);
		if (line[i] && line[i] == COLON)
		{
			if (ft_calloc((void **)&ret[count], 4096, sizeof(char)))
				return (NULL);
			ft_strcpy(ret[count], ft_substr(line, old, i - old));
			old = i + 1;
			count++;
		}
		else if (line[i] && count == words_len - 1)
		{
			if (ft_calloc((void **)&ret[count], 4096, sizeof(char)))
				return (NULL);
			ft_strcpy(ret[count], ft_substr(line, old, ft_strlen(&line[old])));
			count++;
		}
		i++;
	}
	return (ret);
}

void	toggle(int *bo)
{
	if (*bo == FALSE)
		*bo = TRUE;
	else
		*bo = FALSE;
}

void	remove_spaces(char *l)
{
	int		i;
	int		q;
	int		dq;

	q = FALSE;
	dq = FALSE;
	i = 0;
	if (!l)
		return ;
	while (l[i])
	{
		if (l[i] && l[i] == QUOTE)
			toggle(&q);
		else if (l[i] && l[i] == DQUOTE)
			toggle(&dq);
		else if (l[i] && l[i] == BSLASH && l[i + 1] && l[i + 1] == 32)
			i += 2;
		else if (l[i] && l[i] == 32)
		{
			i++;
			while (l[i] && l[i] == 32 && q == FALSE && dq == FALSE)
				remove_char(l, i);
		}
		i++;
	}
}

/* 
** reads line using gnl and feeds t_cmd linked lists 
** i might modify our line in this function, as in removing 
** any unnecessary backslashes,
** quotes, double quotes etc..
** the point is to process our line so that it is readable 
** by our read_cmd function
*/

// currently building a way to know if blocks exist
// colons won't work right now BECUASE OF THE SPLIT

void	process_line(int first)
{
	char	**colon_split;
	int		crashed;
	int		i;

	colon_split = NULL;
	i = 0;
	crashed = FALSE;
	if (first)
		g_info.history_head = ft_create_elem(create_history_struct());
	else
		ft_list_push_front(&g_info.history_head, create_history_struct());
	read_line();
	// modify_line_redir();
	remove_spaces(g_info.line);
	colon_split = ft_split_colon(g_info.line);
	ft_printf("\n");
	do_colon_split(colon_split, i);
	free_tab(&colon_split);
}
