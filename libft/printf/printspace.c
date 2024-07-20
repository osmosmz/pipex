/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:57:54 by mzhuang           #+#    #+#             */
/*   Updated: 2024/06/09 17:47:45 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

void	printleadchar(t_format *format)
{
	unsigned int	length;

	length = max(format->stringlen, format->precision);
	if ((format->flag & FLAG_PLUS) || (!(format->flag & FLAG_ZERO)
			&& format->sign == '-') || (format->flag & FLAG_SPACE
			&& format->sign == '+' && !(format->flag & FLAG_ZERO)))
		length++;
	if (format->flag & FLAG_HASH && !(format->flag & FLAG_ZERO))
		length += 2;
	if (length >= format->width || (format->flag & FLAG_MINUS))
		return ;
	while (format->width > length)
	{
		if (format->flag & FLAG_ZERO)
			ft_putchar_fd('0', 1);
		else
			ft_putchar_fd(' ', 1);
		format->stringlen++;
		length++;
	}
}

void	printendchar(t_format *format)
{
	unsigned int	length;

	length = max(format->stringlen, format->precision);
	if (length >= format->width || !(format->flag & FLAG_MINUS))
		return ;
	while (format->width > length)
	{
		ft_putchar_fd(' ', 1);
		format->stringlen++;
		length++;
	}
}
