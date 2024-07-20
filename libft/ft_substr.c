/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:14:22 by mzhuang           #+#    #+#             */
/*   Updated: 2024/05/19 16:26:31 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Function name ft_substr
// Prototype char *ft_substr(char const *s, unsigned int start,
// size_t len);
// Turn in files -
// Parameters s: The string from which to create the substring.
// start: The start index of the substring in the
// string ’s’.
// len: The maximum length of the substring.
// Return value The substring.
// NULL if the allocation fails.
// External functs. malloc
// Description Allocates (with malloc(3)) and returns a substring
// from the string ’s’.
// The substring begins at index ’start’ and is of
// maximum size ’len

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;

	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	result = malloc((sizeof(char)) * (len + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}
