/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:12:09 by mzhuang           #+#    #+#             */
/*   Updated: 2024/05/18 10:25:39 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The  memmove() function copies n bytes from memory area src to memory
// area dest.  The memory areas may overlap: copying takes place as though
// the bytes in src are first copied into a temporary array that does not
// overlap src or dest, and the bytes are then copied from the temporary
// array to dest.

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d_str;
	unsigned char	*s_str;

	d_str = (unsigned char *)dest;
	s_str = (unsigned char *)src;
	if (d_str > s_str)
	{
		while (n > 0)
		{
			n--;
			d_str[n] = s_str[n];
		}
		return (dest);
	}
	else
		return (ft_memcpy(dest, src, n));
}
