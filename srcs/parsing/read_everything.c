/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:17:51 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/19 14:41:49 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



int			control_d()
{
	int		cursor;

	cursor = g_info.cursor.posx - g_info.prompt_len + 1;
	if (g_info.line && g_info.line[cursor])
	{
		remove_char(g_info.line, cursor);
		tputs(tgoto(tgetstr("cm", NULL), g_info.cursor.posx, \
			g_info.cursor.posy), 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
	}
	else if (!g_info.line || !g_info.line[0])
	{
		ft_printf("exit");
		g_info.crashed = TRUE;
		return (FAILURE);
	}
	return (SUCCESS);
}


void    update_history(t_history *cur)
{
    ft_bzero(cur->line, ft_strlen(cur->line));
    ft_strcpy(cur->line, g_info.line);
}

void    special_keys(char key)
{
    if (key == 27)
        check_for_arrows(g_info.line);
    else if (key == 127)
        delete_key(g_info.line);
}

// g_info.cursor.posx - g_info.prompt_len + 1 : this formula 
//     lets me checkout where cursor is on string
// may be useful to insert or delete characters

int	    read_keys(char key, t_history *cur)
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

int			read_line(void)
{
    t_history   *cur;
    char        key;

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

int	ft_isalpha_ordollar(int c)
{
	if (c == '?' || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

// bslashes within a dquote only work if the following character is a 
//	dollar, a dquote,(a backquote) or another bslash
// not sure whether backquotes should be supported or not 

// other warning : when used solo, a backslash lets you finish a 
//	command in line under current one. 
// should i implement this ?

void	dollar_suite(char *line, char *var, int *index)
{
	int		i;
	t_list	*var_list;
	t_env	*var_key;

	var_list = ft_list_find(g_info.env_head, \
		create_env_struct(var, NULL), cmp_env);
	if (var_list)
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
}

int	dollar(char *line, int *index)
{
	char	*var;
	int		i;

	i = 0;
	var = NULL;
	if (!line[*index] || !line[*index + 1] || (line[*index + 1] && \
		!ft_isalpha_ordollar(line[*index + 1])))
	{
		*index += 1;
		return (FAILURE);
	}
	if (ft_calloc((void **)&var, 256, sizeof(char)))
		return (FAILURE);
	while (line[*index] && (ft_isalpha(line[*index]) || (line[*index] == \
		DOLLAR && i == 0) || (line[*index] == '?')))
	{
		if (i > 0)
			var[i - 1] = line[*index];
		remove_char(line, *index);
		i++;
	}
	dollar_suite(line, var, index);
	return (SUCCESS);
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
				return (FAILURE);
		}
		*index += 1;
	}
	return (SUCCESS);
}

int	count_exceptions(int quote, int dquote)
{
	if (quote % 2 != 0 || dquote % 2 != 0)
		return (1);
	else
		return (0);
}

int	transform_line(char *line, int index, int quote, int dquote)
{
	int		ret;

	ret = 0;
	if (!line)
		return (FAILURE);
	while (line[index] && line[index] != BSLASH && \
		line[index] != QUOTE && line[index] != DQUOTE && line[index] != DOLLAR)
		index++;
	if (line[index] == BSLASH)
		backslash(line, &index, 0);
	if (line[index] == DOLLAR)
		dollar(line, &index);
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
				dollar(line, &index);
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

int			count_words_colon(char *line)
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

char		**ft_split_colon(char *line)
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

void			toggle(int *bo)
{
	if (*bo == FALSE)
		*bo = TRUE;
	else
		*bo = FALSE;
}

void			remove_spaces(char *line)
{
	int		i;
	int		quote;
	int		dquote;

	quote = FALSE;
	dquote = FALSE;
	i = 0;
	if (!line)
		return ;
	while (line[i])
	{
		if (line[i] && line[i] == QUOTE)
			toggle(&quote);
		else if (line[i] && line[i] == DQUOTE)
			toggle(&dquote);
		else if (line[i] && line[i] == BSLASH && line[i + 1] && line[i + 1] == 32)
			i += 2;
		else if (line[i] && line[i] == 32)
		{
			i++;
			while (line[i] && line[i] == 32 && quote == FALSE && dquote == FALSE)
				remove_char(line, i);
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
	while (colon_split && colon_split[i])
	{
		if (transform_line(colon_split[i], 0, 0, 0))
		{
			g_info.cmd_status = 1;
			ft_printf("\nminisheh: parsing error: number of quotes ");
			ft_printf("should be even\n");
			break ;
		}
		read_cmd(colon_split[i], 0, 0);
		i++;
	}
	free_tab(colon_split);
}
