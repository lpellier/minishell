/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:38:35 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/09 14:43:31 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	secure_free(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void		free_blocks(t_list *block_head)
{
	t_list *next;

	while (block_head)
	{
		next = block_head;
		block_head = block_head->next;
		secure_free(next->data);
		secure_free(next);
	}
	secure_free(block_head);
}
