/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_fonctions_other.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 13:32:55 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/26 12:51:35 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	manque_de_place(t_printf *printf, int padlength)
{
	if (printf->padding != 1 || (printf->number == 1 && \
		printf->precision != -1))
		while (padlength--)
			ft_putchar_fd(' ', STDERR_FILENO);
	else
		while (padlength--)
			ft_putchar_fd('0', STDERR_FILENO);
}
