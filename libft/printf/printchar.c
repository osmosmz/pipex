/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printchar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:45:08 by mzhuang           #+#    #+#             */
/*   Updated: 2024/06/09 00:20:51 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printchar(int c, t_format *format)
{
	format->stringlen++;
	printleadchar(format);
	ft_putchar_fd(c, 1);
	printendchar(format);
	return (format->stringlen);
}
