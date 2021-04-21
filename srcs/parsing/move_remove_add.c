/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_remove_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:02:06 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/21 15:05:01 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	prepare_remove(char *line, int q, int dq, int i)
{
	i++;
	while (line[i] && line[i] == 32 && q == FALSE && dq == FALSE)
		remove_char(line, i);
	return (i);
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
			toggle(&q, &i);
		else if (l[i] && l[i] == DQUOTE)
			toggle(&dq, &i);
		else if (l[i] && l[i] == BSLASH && l[i + 1] && l[i + 1] == 32)
			i += 2;
		else if (l[i] && l[i] == 32)
			i = prepare_remove(l, q, dq, i);
		else
			i++;
	}
}

int	add_word(char *word, int where)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (word[i])
	{
		add_char(g_info->line, word[i], where);
		i++;
		where++;
		count++;
	}
	add_char(g_info->line, 32, where);
	count++;
	return (count);
}

int	move_around(char *str, int *start)
{
	int		i;
	int		count;
	int		ret;
	char	**words;

	i = 0;
	ret = 0;
	count = 0;
	words = NULL;
	words = ft_split(str, 32);
	if (!words)
		return (0);
	while (words[i])
	{
		if (i > 0)
		{
			count = add_word(words[i], *start);
			ret += count;
			*start += count;
		}
		i++;
	}
	return (ret);
}

int	remove_words(int i)
{
	int		count;

	count = 0;
	while (g_info->line[i] && g_info->line[i] == 32)
		i++;
	while (g_info->line[i] && g_info->line[i] != 32)
		i++;
	while (g_info->line[i] && g_info->line[i] != '<' && g_info->line[i] != '>')
	{
		count++;
		remove_char(g_info->line, i);
	}
	return (count);
}
