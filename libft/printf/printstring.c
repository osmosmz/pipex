/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printstring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 21:39:38 by mzhuang           #+#    #+#             */
/*   Updated: 2024/06/09 01:05:08 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	getstringlen(char *string, t_format *format)
{
	if (format->iszero)
	{
		if ((format->precision >= 6) || (!((format->flag & FLAG_WIDTH)
					|| format->flag & FLAG_PRECISION)))
			format->arglen = 6;
		else if (format->flag & FLAG_WIDTH && !(format->flag & FLAG_PRECISION))
			format->arglen = 6;
		else
			format->arglen = 0;
	}
	else
	{
		if (ft_strlen(string) > format->precision)
			format->arglen = format->precision;
		else
			format->arglen = ft_strlen(string);
	}
	format->stringlen = format->arglen;
	if (!(format->flag & FLAG_MINUS) && !(format->flag & FLAG_WIDTH))
		format->width = format->arglen;
}

static void	printleadspace(t_format *format)
{
	unsigned int	i;

	i = 0;
	if ((format->flag & FLAG_MINUS))
		return ;
	while (format->width > format->arglen + i)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	format->stringlen += i;
}

static void	printendspace(t_format *format)
{
	unsigned int	i;

	i = 0;
	if (!(format->flag & FLAG_MINUS))
		return ;
	while (format->width > format->arglen + i)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	format->stringlen += i;
}

static void	writestring(char *string, t_format *format)
{
	unsigned int	i;

	i = 0;
	while (i < format->arglen)
	{
		ft_putchar_fd(string[i], 1);
		i++;
	}
}

int	printstring(char *string, t_format *format)
{
	if (string == NULL)
		format->iszero = 1;
	if (format->precision == 0 && !format->iszero
		&& !(format->flag & FLAG_PRECISION))
		format->precision = ft_strlen(string);
	getstringlen(string, format);
	printleadspace(format);
	if (format->iszero && format->arglen)
		ft_putstr_fd("(null)", 1);
	else
		writestring(string, format);
	printendspace(format);
	return (format->stringlen);
}
