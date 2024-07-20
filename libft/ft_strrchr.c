/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:57:08 by mzhuang           #+#    #+#             */
/*   Updated: 2024/05/18 09:33:38 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	len;
	char	*result;

	i = 0;
	result = NULL;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == (char)c)
			result = ((char *)s + i);
		i++;
	}
	return (result);
}
