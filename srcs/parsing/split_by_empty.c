/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_empty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:33:07 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/07 15:15:11 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	calc_line_index(t_info *info, int line_index, char **split)
{
	split[info->w_cnt] = ft_strdup("");
	info->w_cnt++;
	line_index++;
	while (info->lint[line_index + info->lint_index] == _EMPTY_CHAR)
		line_index++;
	return (line_index);
}

int	bzero_n_secure(char **split, t_info *info, char *line, int line_index)
{
	char	*tmp;

	ft_bzero(split[info->w_cnt], LINE_MAX);
	tmp = ft_substr(line, line_index, info->w_ind - line_index);
	ft_strcpy(split[info->w_cnt], tmp);
	secure_free(tmp);
	line_index += info->w_ind - line_index;
	info->w_cnt++;
	return (line_index);
}

int	split_by_empty_suite(t_info *info, char **split, int line_index, char *line)
{
	if (info->lint[line_index + info->lint_index] == _EMPTY_CHAR && \
		!is_empty_or_void(info->lint[line_index + info->lint_index + 1]))
		line_index = calc_line_index(info, line_index, split);
	info->w_ind = line_index;
	while (line[info->w_ind] && info->lint[info->w_ind + info->lint_index] \
		!= -1 && info->lint[info->w_ind + info->lint_index] != _EMPTY)
		info->w_ind++;
	return (line_index);
}

void	split_by_empty(t_info *info, t_cmd *cmd, char *line, int arg_nbr)
{
	char	**split;
	int		line_index;

	line_index = 0;
	info->w_cnt = 0;
	if (ft_calloc((void **)&split, arg_nbr + 1, sizeof(char *)))
		return ;
	while (line[line_index] && info->lint[line_index + info->lint_index] != -1)
	{
		line_index = split_by_empty_suite(info, split, line_index, line);
		if (info->w_ind - line_index > 0)
		{
			if (ft_calloc((void **)&split[info->w_cnt], LINE_MAX, sizeof(char)))
				return ;
			line_index = bzero_n_secure(split, info, line, line_index);
		}
		line_index++;
	}
	split[info->w_cnt] = NULL;
	cmd->args = split;
	init_cmd_lint(info, cmd);
	info->lint_index += line_index + 1;
	info->line_index = line_index;
}
