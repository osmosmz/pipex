/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:53:23 by mzhuang           #+#    #+#             */
/*   Updated: 2024/05/19 13:16:08 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The memcpy() function copies n bytes from memory area src to memory area
// dest.  The memory areas must not overlap.  Use memmove(3) if the memory
// areas do overlap.

// The memcpy() function returns a pointer to dest.

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (dest);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
