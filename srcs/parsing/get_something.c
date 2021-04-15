/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_something.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:57:47 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/15 16:39:09 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		complete_portion(char *line, int index, int block_end)
{
	int		i;

	i = block_end - index;
	while (line[i] && is_whitespace(line[i]))
		i++;
	return (i);
}

int	get_input(char *line, t_cmd *cmd, int index)
{
	int		block_end;
	int		i;

	i = 0;
	block_end = check_if_block(index);
	if (block_end >= 0)
	{
		block_end = complete_portion(line, index, block_end);
		cmd->input = ft_strndup(line, block_end);
	}
	else
	{
		while (line[i] && ft_cinset(line[i], SEPARATOR))
			i++;
		while (line[i - 1] == 32)
			i--;
		if (i >= 1)
			cmd->input = ft_strndup(line, i);
		else
			cmd->input = NULL;
	}
	return (ft_strlen(cmd->input));
}

int	get_option(char *line, t_cmd *cmd, int index)
{
	int		block_end;
	char	**words;

	block_end = check_if_block(index);
	if (block_end >= 0 && line[0] == '-')
	{
		block_end = complete_portion(line, index, block_end);
		cmd->option = ft_strndup(line, block_end);
	}
	else
	{
		words = ft_split(line, 32);
		if (words && words[0] && words[0][0] == '-')
			if (!str_isalpha_withminus(words[0]))
				cmd->option = ft_strdup(words[0]);
		free_tab(words);
	}
	return (ft_strlen(cmd->option));
}


int	get_cmd(char *line, t_cmd *cmd, int index)
{
	char	**words;
	int		block_end;
	int		i;

	i = 0;
	block_end = check_if_block(index);
	if (block_end >= 0)
	{
		block_end = complete_portion(line, index, block_end);
		cmd->cmd = ft_strndup(line, block_end);
	}
	else
	{
		if (line && line[i] && !ft_cinset(line[i], SEPARATOR))
			return (0);
		words = ft_split(line, 32);
		while (words && words[0][i])
		{
			if (words[0][i] >= 65 && words[0][i] <= 90)
				words[0][i] += 32;
			i++;
		}
		if (words && words[0])
			cmd->cmd = ft_strdup(words[0]);
		free_tab(words);
	}
	return (ft_strlen(cmd->cmd));
}
