/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:55:49 by mzhuang           #+#    #+#             */
/*   Updated: 2024/05/18 10:30:07 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The  memchr()  function scans the initial n bytes of the memory area
// pointed to by s for the first instance of c.  Both c and the bytes of the
// memory area pointed to by s are interpreted as unsigned char.

// The memchr() and memrchr() functions return a pointer to the matching byte
// or NULL if the character does not occur in the given memory area.

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*result;

	i = 0;
	result = (unsigned char *)(s);
	while (i < n)
	{
		if (result[i] == (unsigned char)c)
		{
			return ((void *)s + i);
		}
		i++;
	}
	return (NULL);
}
