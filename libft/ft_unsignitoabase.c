/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsignitoabase.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:21:26 by mzhuang           #+#    #+#             */
/*   Updated: 2024/07/08 22:44:44 by mzhuang          ###   ########.fr       */
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

static unsigned int	ft_getnumdigits(unsigned long int n, unsigned int baselen)
{
	int	len;

	if (n == 0)
		return (1);
	else
		len = 0;
	while (n > 0)
	{
		n /= baselen;
		len++;
	}
	return (len);
}

char	*ft_unsignitoabase(unsigned long int n, char *base)
{
	unsigned int	len;
	char			*result;
	unsigned int	baselen;

	baselen = ft_strlen(base);
	len = ft_getnumdigits(n, baselen);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len > 0)
	{
		result[len - 1] = base[n % baselen];
		n /= baselen;
		len--;
	}
	return (result);
}
