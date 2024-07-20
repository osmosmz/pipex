/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:00:39 by mzhuang           #+#    #+#             */
/*   Updated: 2024/06/09 00:40:06 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	cleanup(t_format *format)
{
	if ((format->flag & FLAG_PRECISION) || (format->flag & FLAG_PLUS))
		format->flag &= ~FLAG_ZERO;
	if (!ft_strchr("xXp", format->type))
		format->flag &= ~FLAG_HASH;
	if (format->flag & FLAG_PLUS)
		format->flag &= ~FLAG_SPACE;
	if (format->type == 'c')
	{
		format->flag &= ~FLAG_ZERO;
		format->precision = 0;
	}
	if (format->type == 'p')
		format->flag |= FLAG_HASH;
}

int	printargs(va_list arg, const char **string, t_format *format)
{
	if (parser(string, format) == -1)
		return (-1);
	cleanup(format);
	if (format->type == 'c')
		return (printchar(va_arg(arg, int), format));
	else if (ft_strchr("di", format->type))
		return (printint(va_arg(arg, int), format));
	else if (ft_strchr("p", format->type))
		return (printunsigned(va_arg(arg, unsigned long long), format));
	else if (ft_strchr("uxX", format->type))
		return (printunsigned(va_arg(arg, unsigned int), format));
	else if (format->type == 's')
		return (printstring(va_arg(arg, char *), format));
	else if (format->type == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	else
		return (-1);
}
