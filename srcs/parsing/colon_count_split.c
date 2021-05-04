/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colon_count_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:02:55 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/04 14:01:07 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		count_cmd(char *line, int *lint)
{
	int		count;
	int		i;

	i = 0;
	count = 1;
	while (line[i] && lint[i] != -1)
	{
		if (line[i] == COLON && lint[i] == _SEP)
			count++;
		i++;
	}
	return (count);
}

void	create_cmd_list(t_info *info, int nbr)
{
	int		i;

	i = 1;
	info->cmd_head = ft_create_elem(create_cmd_struct());
	while (i < nbr)
	{
		ft_list_push_back(&info->cmd_head, create_cmd_struct());
		i++;
	}
}

char	**split_by_colon(t_info *info, char *line, int *lint)
{
	char	**split;
	char	*tmp;
	int		line_index;
	int		word_index;
	int		word_count;
	int		cmd_nbr;

	line_index = 0;
	tmp = NULL;
	word_count = 0;
	cmd_nbr = count_cmd(line, lint);
	if (ft_calloc((void **)&split, cmd_nbr + 1, sizeof(char *)))
		return (NULL);
	create_cmd_list(info, cmd_nbr);
	while (line[line_index] && lint[line_index] != -1)
	{
		word_index = line_index;
		while (line[word_index] && lint[word_index] != -1)
		{
			if (line[word_index] == COLON && lint[word_index] == _SEP)
				break ;
			word_index++;
		}
		if (word_index - line_index > 0)
		{
			secure_free(tmp);
			tmp = ft_substr(line, line_index, word_index - line_index);
			if (ft_calloc((void **)&split[word_count], LINE_MAX, sizeof(char)))
				return (NULL);
			ft_strcpy(split[word_count], tmp); 
			line_index += word_index - line_index;
			word_count++;
		}
		line_index++;
	}
	split[word_count] = NULL;
	return (split);
}
