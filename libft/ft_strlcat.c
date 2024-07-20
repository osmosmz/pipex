/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 01:59:06 by mzhuang           #+#    #+#             */
/*   Updated: 2024/05/19 11:22:12 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  The strlcat() function appends the NUL-terminated string src to the end
//      of dst.  It will append at most size - strlen(dst) - 1 bytes, NUL-termi‐
//      nating the result.

// it will return total length of src + dest

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;

	i = 0;
	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	if (d_len >= dstsize)
		return (dstsize + s_len);
	while (d_len + i < dstsize - 1 && src[i])
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = '\0';
	return (d_len + s_len);
}
