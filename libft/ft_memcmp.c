/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:14:49 by mzhuang           #+#    #+#             */
/*   Updated: 2024/05/18 10:25:34 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The memcmp() function compares the first n bytes (each interpreted as
// unsigned char) of the memory areas s1 and s2.

// The  memcmp() function returns an integer less than, equal to, or greater
// than zero if the first n bytes of s1 is found, respectively, to be less
// than, to match, or be greater than the first n bytes of s2.

// For a nonzero return value, the sign is determined by the sign of the
// difference between the first pair of bytes (interpreted as unsigned char)
// that differ in s1 and s2.

// If n is zero, the return value is zero.

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			break ;
		i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
