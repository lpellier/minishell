/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:38:35 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/22 17:42:43 by lpellier         ###   ########.fr       */
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
