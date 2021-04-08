/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:24:47 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/08 16:36:44 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	str_isalpha_withminus(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '-')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	cmp_block(void *data, void *data_ref)
{
	t_block		*ptr;
	t_block		*ptr_ref;

	ptr = (t_block *)data;
	ptr_ref = (t_block *)data_ref;
	if (ptr->start == ptr_ref->start && ptr->end - ptr->start > 0)
		return (SUCCESS);
	else
		return (FAILURE);
}

int	check_if_block(int index)
{
	t_list		*ptr;
	t_block		*block;

	ptr = ft_list_find(g_info.block_head, \
		create_block_struct(index, -1), cmp_block);
	if (!ptr)
		return (-1);
	block = ptr->data;
	return (block->end);
}

int	get_input(char *line, t_cmd *cmd, int index)
{
	int		block_end;
	int		i;

	i = 0;
	block_end = check_if_block(index);
	if (block_end >= 0)
		cmd->input = ft_strndup(line, block_end - index);
	else
	{
		while (line[i] && ft_cinset(line[i], SEPARATOR))
			i++;
		if (i >= 1)
			cmd->input = ft_strndup(line, i);
		else
			cmd->input = NULL;
	}
	return (ft_strlen(cmd->input));
}

int	get_option(char *line, t_cmd *cmd, int index)
{
	char	**words;

	if (check_if_block(index) >= 0)
		cmd->option = NULL;
	else
	{
		words = ft_split(line, 32);
		if (words && words[0] && words[0][0] == '-')
			if (!str_isalpha_withminus(words[0]))
				cmd->option = ft_strdup(words[0]);
		free_tab(&words);
	}
	return (ft_strlen(cmd->option));
}
