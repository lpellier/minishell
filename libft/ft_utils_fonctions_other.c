/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_fonctions_other.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 13:32:55 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/07 13:33:18 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	manque_de_place(t_printf *printf, int padlength)
{
	if (printf->padding != 1 || (printf->number == 1 && \
		printf->precision != -1))
		while (padlength--)
			ft_putchar_fd(' ', 1);
	else
		while (padlength--)
			ft_putchar_fd('0', 1);
}
