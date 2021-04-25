/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colon_count_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:02:55 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/25 20:07:20 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (line[i] && line[i] == BSLASH)
			i += 2;
		if (line[i] && line[i] == COLON)
			count++;
		i++;
	}
	return (count);
}

char	**split_colon_suite(char *line, t_split *splt)
{
	while (line[splt->i])
	{
		splt->i = pass_q_and_dq(line, splt->i);
		if (line[splt->i] && line[splt->i] == COLON)
		{
			if (ft_calloc((void **)&splt->ret[splt->count], 4096, sizeof(char)))
				return (NULL);
			ft_strcpy(splt->ret[splt->count], ft_substr(line, splt->old, \
				splt->i - splt->old));
			splt->old = splt->i + 1;
			splt->count++;
		}
		else if (line[splt->i] && splt->count == (count_words_colon(line) - 1))
		{
			if (ft_calloc((void **)&splt->ret[splt->count], 4096, sizeof(char)))
				return (NULL);
			ft_strcpy(splt->ret[splt->count], ft_substr(line, splt->old, \
				ft_strlen(&line[splt->old])));
			splt->count++;
		}
		splt->i++;
	}
	return (splt->ret);
}

char	**ft_split_colon(char *line)
{
	t_split	split;

	split.i = 0;
	split.words_len = count_words_colon(line);
	split.old = 0;
	split.count = 0;
	split.ret = NULL;
	if (ft_calloc((void **)&split.ret, split.words_len + 1, sizeof(char *)))
		return (NULL);
	if (split.words_len == 1)
	{
		if (ft_calloc((void **)&split.ret[0], 4096, sizeof(char)))
			return (NULL);
		ft_strcpy(split.ret[0], line);
		return (split.ret);
	}
	split.ret = split_colon_suite(line, &split);
	return (split.ret);
}
