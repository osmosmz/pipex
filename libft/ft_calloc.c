/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:29:14 by mzhuang           #+#    #+#             */
/*   Updated: 2024/05/19 13:23:04 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The  calloc() function allocates memory for an array of nmemb elements of
// size bytes each and returns a pointer to the allocated memory.  The memory
// is set to zero.  If nmemb or size is 0, then calloc() returns either NULL,
// or a unique pointer value that can later be successfully passed to free().
// If the multiplication of nmemb and size would result in integer overflow,
// then calloc() returns an error.  By contrast, an integer overflow would not
// be detected in the following call to malloc(), with the result that an
// incorrectly sized block of memory would be allocated:

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	if (size > 0 && nmemb > ((size_t)-1) / size)
		return (NULL);
	result = malloc(size * nmemb);
	if (!result)
		return (NULL);
	ft_bzero(result, size * nmemb);
	return (result);
}
