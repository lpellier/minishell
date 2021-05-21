/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 19:07:47 by lpellier          #+#    #+#             */
/*   Updated: 2021/05/21 19:08:14 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	gross_check(char *arg, int i, int neg)
{
	int	eighteen;

	eighteen = c_to_int(arg[18 + i]);
	if (neg == 0 && eighteen > 7)
		eighteen = 1;
	else if (neg == 1 && eighteen > 8)
		eighteen = 1;
	else
		eighteen = 0;
	if (c_to_int(arg[1 + i]) > 2 || c_to_int(arg[2 + i]) > 2 || \
		c_to_int(arg[3 + i]) > 3 || c_to_int(arg[4 + i]) > 3 || \
		c_to_int(arg[5 + i]) > 7 || c_to_int(arg[6 + i]) > 2 || \
		c_to_int(arg[7 + i]) > 0 || c_to_int(arg[8 + i]) > 3 || \
		c_to_int(arg[9 + i]) > 6 || c_to_int(arg[10 + i]) > 8 || \
		c_to_int(arg[11 + i]) > 5 || c_to_int(arg[12 + i]) > 4 || \
		c_to_int(arg[13 + i]) > 7 || c_to_int(arg[14 + i]) > 7 || \
		c_to_int(arg[15 + i]) > 5 || c_to_int(arg[16 + i]) > 8 || \
		c_to_int(arg[17 + i]) > 0 || eighteen)
		return (SUCCESS);
	else
		return (FAILURE);
}

int	exceeds_limit(char *arg)
{
	int	i;
	int	neg;

	i = 0;
	neg = 0;
	while (arg[i] == '+' || arg[i] == '-')
		i++;
	if (arg[0] == '-')
		neg = 1;
	if (ft_strlen(arg) < 19 + i)
		return (FAILURE);
	else if (ft_strlen(arg) > 19 + i)
		return (SUCCESS);
	return (gross_check(arg, i, neg));
}

int	int_errors(char *arg)
{
	int			i;
	long long	value;

	i = 0;
	while (arg[i] == '+' || arg[i] == '-')
		i++;
	if (i > 1)
		return (SUCCESS);
	if (!str_is_alpha(arg) || !exceeds_limit(arg))
		return (SUCCESS);
	value = ft_llong_atoi(arg);
	return (FAILURE);
}
