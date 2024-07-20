/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:11:21 by mzhuang           #+#    #+#             */
/*   Updated: 2024/05/20 01:08:18 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Function name ft_strtrim
// Prototype char *ft_strtrim(char const *s1, char const *set);
// Turn in files -
// Parameters s1: The string to be trimmed.
// set: The reference set of characters to trim.
// Return value The trimmed string.
// NULL if the allocation fails.
// External functs. malloc
// Description Allocates (with malloc(3)) and returns a copy of
// ’s1’ with the characters specified in ’set’ removed
// from the beginning and the end of the string.

#include "libft.h"

static unsigned int	findcount(char const *s1, char const *set, size_t location)
{
	int				counter;
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	if (location == 0)
		counter = 1;
	else
	{
		counter = -1;
		location--;
	}
	while (set[i])
	{
		if (set[i] != s1[location])
			i++;
		else
		{
			location += counter;
			count++;
			i = 0;
		}
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	startcount;
	unsigned int	endcount;
	size_t			len;

	len = ft_strlen(s1);
	startcount = 0;
	startcount = findcount(s1, set, 0);
	if (startcount == len)
		return (ft_strdup(""));
	endcount = findcount(s1, set, len);
	return (ft_substr(s1, startcount, len - startcount - endcount));
}
