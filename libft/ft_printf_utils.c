/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 13:37:59 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/07 14:11:51 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	return_written(const char *format, t_printf *printf)
{
	int	written;

	print_before(format, printf);
	written = printf->outputlen;
	free(printf);
	return (written);
}
