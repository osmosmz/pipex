/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printintutil.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:47:29 by mzhuang           #+#    #+#             */
/*   Updated: 2024/06/08 22:06:12 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_unsigned_fd(unsigned long long num, t_format *format)
{
	char	*base;

	if (format->precision == 0 && format->iszero
		&& format->flag & FLAG_PRECISION)
		return ;
	if (format->base == 10)
		base = "0123456789";
	else if (format->base == 16)
		base = "0123456789abcdef";
	if (format->upper == 1)
		base = "0123456789ABCDEF";
	if (num >= format->base)
	{
		write_unsigned_fd(num / format->base, format);
		write(1, &base[num % format->base], 1);
	}
	else
		write(1, &base[num % format->base], 1);
}

void	printprecision(t_format *format)
{
	int	i;

	i = 0;
	while (format->precision > format->arglen + i)
	{
		ft_putchar_fd('0', 1);
		i++;
	}
	format->stringlen += i;
}

void	printsign(t_format *format)
{
	if (format->flag & FLAG_PLUS || format->sign == '-')
	{
		ft_putchar_fd(format->sign, 1);
		format->stringlen++;
	}
	if (format->flag & FLAG_SPACE && format->sign == '+')
	{
		ft_putchar_fd(' ', 1);
		format->stringlen++;
	}
}
