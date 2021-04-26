/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_otherss.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 13:31:35 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/26 10:38:20 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	reduce_me(t_printf *printf, unsigned int res)
{
	put_zeros(printf);
	ft_putunbr_fd(res, STDERR_FILENO);
	output_flags(printf);
}
