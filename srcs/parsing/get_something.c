/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_something.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:57:47 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/12 13:59:28 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	get_cmd(char *line, t_cmd *cmd, int index)
{
	char	**words;
	int		block_end;
	int		i;

	i = 0;
	block_end = check_if_block(index);
	if (block_end >= 0)
		cmd->cmd = ft_strndup(line, block_end - index);
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
		free_tab(&words);
	}
	return (ft_strlen(cmd->cmd));
}
