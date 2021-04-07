/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_otherss.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 13:31:35 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/07 13:33:25 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	reduce_me(t_printf *printf, unsigned int res)
{
	put_zeros(printf);
	ft_putunbr_fd(res, 1);
	output_flags(printf);
}
