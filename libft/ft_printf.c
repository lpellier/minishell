/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaspellier <lucaspellier@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 10:56:23 by lpellier          #+#    #+#             */
/*   Updated: 2020/03/25 19:53:09 by lucaspellie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Une specification de conversion se compose de champs facultatifs et
**	obligatoires mis en forme comme suit :
**	%[flags][width][.precision][size]type
**
**	Flags :
**	- = aligner a gauche le resultat selon la largeur de champ donnee
**	0 = Si width est prefixe par 0, des zeros non significatifs sont ajoutes
**	jusqu'a ce que la largeur minimale soit atteinte. Si 0 et - apparaissent,
**	0 est ignore.
**  * = si width = *, alors le prochain argument definit width.
**
**	Width : largeur de l'output - si elle est superieure a l'output, on
**	complete avec des espaces pour fill (ou des 0 si un seul flag = 0)
**
**	Precision :
**	. = suivi d'un entier decimal positif qui selon le type de conversion,
**	va affecter differemment l'output.
**		c -> aucun effet
**		s -> nombre max de caracteres a imprimer
**		d, i, u, x, X -> nombre min de chiffres a imprimer (par defaut a un)
**		si le nombre de chiffres de l'arg est inferieur a precision, la valeur
**		de sortie est remplie a gauche de 0 (si precision = 0 et valeur a
**		convertir = 0 -> pas d'output).
**
**	Type :
**	c = Character;													--> fait
**	s =	String;														--> fait
**	p =	Pointer Type -> output arg under the form of an adress		--> fait
**		containing hexadecimal numbers;
**	d = Int decimal;												--> fait
**	i = same as d;													--> fait
**	u = Unsigned int;												--> fait
**	x = Hexadecimal number (abcdef);								--> fait
**	X = Hexadecimal number (ABCDEF);								--> fait
**
**	ETAPE 1 : ARRIVER A CHOPPER LA BONNE CONVERSION;	--> fait
**	ETAPE 2 : GESTION DE LA WIDTH;		 				--> fait
**	ETAPE 3 : GESTION DES FLAGS;						--> fait
**	ETAPE 4 ; GESTION DE LA PRECISION;					--> fait
**	ETAPE 5 : GESTION D'ERREURS;						--> fait
**	ETAPE INTERMEDIAIRE GERER LE PRINT DANS FORMAT;		--> fait
**	ETAPE 6 : GERER PLUSIEURS ARGUMENTS;				--> fait
**	ETAPE 7 : PROFIT!;
*/

int		ft_isinset(char c, char *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		count_format(const char *format)
{
	int	count;

	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			while (!ft_isinset(*format, CONVERTER) && *format)
				format++;
			count = ft_isinset(*format, CONVERTER) ? count + 1 : count;
		}
		format++;
	}
	return (count);
}

void	ft_init_info(t_printf *info)
{
	info->padding = 0;
	info->width = 0;
	info->number = 0;
	info->precision = -1;
	info->plus = 0;
	info->minus = 0;
	info->perc = 0;
	info->space = 0;
	info->len = 0;
	info->orig = 0;
	info->type = 48;
}

void	ft_parse_and_print(const char *format, t_printf *info, va_list ap)
{
	while (info->count--)
	{
		ft_init_info(info);
		format = ft_fill_struct(format, info, ap);
		ft_output(info, ap);
		if (info->count != 0)
			format = print_aoutsider(format, info);
		else
			print_aoutsider(format, info);
	}
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	t_printf	*info;
	int			written;

	if (!(info = (t_printf *)malloc(sizeof(t_printf))))
		return (-1);
	info->outputlen = 0;
	if (count_format(format) == 0)
	{
		print_before(format, info);
		written = info->outputlen;
		free(info);
		return (written);
	}
	va_start(ap, format);
	info->count = (count_format(format) == 1 ? 1 : count_format(format) + 1);
	format = (*format == '%' ? format + 1 : print_before(format, info));
	ft_parse_and_print(format, info, ap);
	va_end(ap);
	written = info->outputlen;
	free(info);
	return (written);
}
