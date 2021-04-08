/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:38:05 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/08 13:44:50 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_history	*create_history_struct(void)
{
	t_history	*history;

	if (ft_calloc((void **)&history, 1, sizeof(t_history)))
		return (NULL);
	if (ft_calloc((void **)&history->line, LINE_MAX, sizeof(char)))
		return (NULL);
	return (history);
}

t_block	*create_block_struct(int a, int b)
{
	t_block	*block;

	if (ft_calloc((void **)&block, 1, sizeof(t_block)))
		return (NULL);
	block->start = a;
	block->end = b;
	return (block);
}
