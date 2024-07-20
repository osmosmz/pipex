/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:21:26 by mzhuang           #+#    #+#             */
/*   Updated: 2024/05/19 10:53:28 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Function name ft_itoa
// Prototype char *ft_itoa(int n);
// Turn in files -
// Parameters n: the integer to convert.
// Return value The string representing the integer.
// NULL if the allocation fails.
// External functs. malloc
// Description Allocates (with malloc(3)) and returns a string
// representing the integer received as an argument.
// Negative numbers must be handled.

#include "libft.h"

static int	ft_getnumdigits(int n, int *sign)
{
	int	len;

	if (n == 0)
		return (1);
	else if (n < 0)
	{
		(*sign)++;
		n /= 10;
		n *= -1;
		len = 1;
	}
	else
		len = 0;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static unsigned int	ft_abs(int n)
{
	if (n < 0)
		return ((unsigned int)-n);
	else
		return (n);
}

char	*ft_itoa(int n)
{
	int				len;
	char			*result;
	unsigned int	postive_n;
	int				sign;

	sign = 0;
	len = ft_getnumdigits(n, &sign);
	result = malloc(sizeof(char) * (len + sign + 1));
	if (!result)
		return (NULL);
	if (sign)
		result[0] = '-';
	result[len + sign] = '\0';
	postive_n = ft_abs(n);
	while (len > 0)
	{
		result[len + sign - 1] = postive_n % 10 + '0';
		postive_n /= 10;
		len--;
	}
	return (result);
}
