/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:40:44 by mzhuang           #+#    #+#             */
/*   Updated: 2024/06/08 19:11:32 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	getflags(const char **string, t_format *format)
{
	while (ft_strchr(FLAGS, **string))
	{
		if (**string == '#')
			format->flag |= FLAG_HASH;
		else if (**string == '0')
			format->flag |= FLAG_ZERO;
		else if (**string == '-')
			format->flag |= FLAG_MINUS;
		else if (**string == ' ')
			format->flag |= FLAG_SPACE;
		else
			format->flag |= FLAG_PLUS;
		(*string)++;
	}
}

static void	getwidth(const char **string, t_format *format)
{
	int	width;

	width = 0;
	if (ft_isdigit(**string))
		format->flag |= FLAG_WIDTH;
	while (ft_isdigit(**string))
	{
		width *= 10;
		width += **string - '0';
		(*string)++;
	}
	format->width = width;
}

static void	getprecision(const char **string, t_format *format)
{
	int	precision;

	precision = 0;
	if (**string == '.')
	{
		format->flag |= FLAG_PRECISION;
		(*string)++;
		while (ft_isdigit(**string))
		{
			precision *= 10;
			precision += **string - '0';
			(*string)++;
		}
		format->precision = precision;
	}
}

static void	gettype(const char **string, t_format *format)
{
	if (ft_strchr(TYPES, **string))
		format->type = **string;
	if ((ft_strchr("xXp", **string)))
	{
		format->base = 16;
		if (**string == 'X')
			format->upper = 1;
	}
}

int	parser(const char **string, t_format *format)
{
	getflags(string, format);
	getwidth(string, format);
	getprecision(string, format);
	gettype(string, format);
	if (format->type == 0)
		return (-1);
	return (0);
}
