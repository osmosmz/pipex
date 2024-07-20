/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:13:18 by mzhuang           #+#    #+#             */
/*   Updated: 2024/05/19 09:36:55 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Function name ft_strjoin
// Prototype char *ft_strjoin(char const *s1, char const *s2);
// Turn in files -
// Parameters s1: The prefix string.
// s2: The suffix string.
// Return value The new string.
// NULL if the allocation fails.
// External functs. malloc
// Description Allocates (with malloc(3)) and returns a new
// string, which is the result of the concatenation
// of ’s1’ and ’s2’.

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	t_len;

	t_len = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(sizeof(char) * (1 + t_len));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, ft_strlen(s1) + 1);
	ft_strlcat(result, s2, t_len + 1);
	return (result);
}
