/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:33:24 by mzhuang           #+#    #+#             */
/*   Updated: 2024/06/07 21:58:13 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	initialise(t_format *format)
{
	format->flag = 0;
	format->width = 0;
	format->precision = 0;
	format->type = 0;
	format->arglen = 0;
	format->stringlen = 0;
	format->base = 10;
	format->upper = 0;
	format->sign = 0;
	format->iszero = 0;
}

int	ft_printf(const char *input, ...)
{
	va_list		args;
	t_format	format;
	int			count;

	va_start(args, input);
	count = 0;
	while (*input)
	{
		if (*input == '%')
		{
			initialise(&format);
			input++;
			count += printargs(args, (&input), &format);
		}
		else
		{
			ft_putchar_fd(*input, 1);
			count++;
		}
		input++;
	}
	va_end(args);
	return (count);
}
