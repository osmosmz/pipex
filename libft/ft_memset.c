/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:44:47 by mzhuang           #+#    #+#             */
/*   Updated: 2024/05/15 19:49:44 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The memset() function fills the first n bytes of the memory area pointed
// to by s with the constant byte c.

//        The memset() function returns a pointer to the memory area s.

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*result;
	size_t			i;

	i = 0;
	result = (unsigned char *)s;
	while (i < n)
	{
		result[i] = c;
		i++;
	}
	return (s);
}
