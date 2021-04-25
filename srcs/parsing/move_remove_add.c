/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_remove_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:02:06 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/25 19:02:58 by lpellier         ###   ########.fr       */
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

int	add_word(char *str, char *word, int where)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (word[i])
	{
		add_char(str, word[i], where);
		i++;
		where++;
		count++;
	}
	add_char(str, 32, where);
	count++;
	return (count);
}

int	move_around(char *line, char *str, int *start)
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
			count = add_word(line, words[i], *start);
			ret += count;
			*start += count;
		}
		i++;
	}
	free_tab(&words);
	return (ret);
}

int	remove_words(char *str, int i)
{
	int		count;

	count = 0;
	while (str[i] && str[i] == 32)
		i++;
	while (str[i] && str[i] != 32)
		i++;
	while (str[i] && str[i] != '<' && str[i] != '>')
	{
		count++;
		remove_char(str, i);
	}
	return (count);
}
