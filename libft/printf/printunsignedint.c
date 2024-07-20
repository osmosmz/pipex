/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printunsignedint.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:45:08 by mzhuang           #+#    #+#             */
/*   Updated: 2024/06/09 00:59:02 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print0x(t_format *format)
{
	if (format->flag & FLAG_HASH)
	{
		if (format->upper == 1)
			ft_putstr_fd("0X", 1);
		else
			ft_putstr_fd("0x", 1);
		format->stringlen += 2;
	}
}

static void	getintlen(unsigned long long num, t_format *format)
{
	if (format->iszero && (format->precision > 0
			|| !(format->flag & FLAG_PRECISION)))
	{
		if (format->type == 'p')
			format->arglen = 5;
		else
			format->arglen = 1;
	}
	while (num > 0)
	{
		num /= format->base;
		format->arglen++;
	}
	format->stringlen = format->arglen;
}

int	printunsigned(unsigned long long number, t_format *format)
{
	if (number == 0)
	{
		format->iszero = 1;
		format->flag &= ~FLAG_HASH;
	}
	getintlen(number, format);
	if (format->flag & FLAG_ZERO)
	{
		print0x(format);
		printleadchar(format);
	}
	else
	{
		printleadchar(format);
		print0x(format);
	}
	printprecision(format);
	if (format->type == 'p' && format->iszero)
		ft_putstr_fd("(nil)", 1);
	else
		write_unsigned_fd(number, format);
	printendchar(format);
	return (format->stringlen);
}
