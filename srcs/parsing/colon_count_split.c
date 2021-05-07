/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colon_count_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:02:55 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/07 15:03:53 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_cmd(char *line, int *lint)
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

int	split_by_colon_suite(t_info *info, int line_index, char *line, char **split)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_substr(line, line_index, info->w_ind - line_index);
	if (ft_calloc((void **)&split[info->w_cnt], LINE_MAX, sizeof(char)))
		return (FAILURE);
	ft_strcpy(split[info->w_cnt], tmp);
	secure_free(tmp);
	line_index += info->w_ind - line_index;
	info->w_cnt++;
	return (line_index);
}

char	**split_by_colon(t_info *info, char *line, int *lint)
{
	char	**split;
	int		line_index;
	int		cmd_nbr;

	line_index = 0;
	info->w_cnt = 0;
	cmd_nbr = count_cmd(line, lint);
	if (ft_calloc((void **)&split, cmd_nbr + 1, sizeof(char *)))
		return (NULL);
	create_cmd_list(info, cmd_nbr);
	while (line[line_index] && lint[line_index] != -1)
	{
		info->w_ind = line_index;
		while (line[info->w_ind] && lint[info->w_ind] != -1)
		{
			if (line[info->w_ind] == COLON && lint[info->w_ind] == _SEP)
				break ;
			info->w_ind++;
		}
		if (info->w_ind - line_index > 0)
			line_index = split_by_colon_suite(info, line_index, line, split);
		line_index++;
	}
	split[info->w_cnt] = NULL;
	return (split);
}
