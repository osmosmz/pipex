/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:45:08 by mzhuang           #+#    #+#             */
/*   Updated: 2024/06/09 00:54:39 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	getintlen(long c, t_format *format)
{
	if (c == 0 && (format->precision > 0 || !(format->flag & FLAG_PRECISION)))
		format->arglen = 1;
	while (c > 0)
	{
		c /= format->base;
		format->arglen++;
	}
	format->stringlen = format->arglen;
}

static void	setsign(long *c, t_format *format)
{
	if (*c < 0)
	{
		format->sign = '-';
		*c *= -1;
	}
	else if (*c == 0)
	{
		format->iszero = 1;
		format->sign = '+';
	}
	else
		format->sign = '+';
}

int	printint(int c, t_format *format)
{
	long	temp;

	temp = c;
	setsign(&temp, format);
	getintlen(temp, format);
	if (format->flag & FLAG_ZERO)
	{
		printsign(format);
		printleadchar(format);
	}
	else
	{
		printleadchar(format);
		printsign(format);
	}
	printprecision(format);
	write_unsigned_fd(temp, format);
	printendchar(format);
	return (format->stringlen);
}
