/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:13:36 by mzhuang           #+#    #+#             */
/*   Updated: 2024/06/30 21:43:14 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define FLAG_HASH 1
# define FLAG_ZERO 2
# define FLAG_MINUS 4
# define FLAG_SPACE 8
# define FLAG_PLUS 16
# define FLAG_WIDTH 32
# define FLAG_PRECISION 64

# define FLAGS "#0- +"
# define PRECISION '.'
# define TYPES "cspdiuxX%"

typedef struct s_format
{
	int					flag;
	unsigned int		width;
	unsigned int		precision;
	char				type;
	unsigned int		arglen;
	int					stringlen;
	unsigned long long	base;
	int					upper;
	int					iszero;
	char				sign;

}						t_format;

int						parser(const char **string, t_format *format);
int						printargs(va_list arg, const char **input,
							t_format *format);
int						ft_printf(const char *input, ...);
void					printleadchar(t_format *format);
void					printendchar(t_format *format);
int						printchar(int c, t_format *format);
int						printint(int c, t_format *format);
int						printunsigned(unsigned long long c, t_format *format);

void					write_unsigned_fd(unsigned long long num,
							t_format *format);
void					printprecision(t_format *format);
void					printsign(t_format *format);
int						printstring(char *string, t_format *format);

#endif