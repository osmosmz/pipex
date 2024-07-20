/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:10:09 by mzhuang           #+#    #+#             */
/*   Updated: 2024/05/20 00:29:35 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Function name ft_split
// Prototype char **ft_split(char const *s, char c);
// Turn in files -
// Parameters s: The string to be split.
// c: The delimiter character.
// Return value The array of new strings resulting from the split.
// NULL if the allocation fails.
// External functs. malloc, free
// Description Allocates (with malloc(3)) and returns an array
// of strings obtained by splitting ’s’ using the
// character ’c’ as a delimiter. The array must end
// with a NULL pointer.

#include "libft.h"

static unsigned int	countword(char const *s, char c)
{
	unsigned int	count;
	unsigned int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
			{
				i++;
				if (s[i] == '\0')
					return (count);
			}
		}
		i++;
	}
	return (count);
}

unsigned int	findlen(char const *s, char c, unsigned int *startindex,
		unsigned int *delimiters)
{
	unsigned int	wordlen;
	unsigned int	i;

	i = *startindex;
	wordlen = 0;
	while (s[i] == c && s[i])
		i++;
	*delimiters = (i - *startindex);
	while (s[i + wordlen] != c && s[i + wordlen])
		wordlen++;
	*startindex = i + wordlen;
	return (wordlen);
}

char	*allocwords(char const *s, char c, unsigned int *startindex)
{
	unsigned int	wordlen;
	unsigned int	delimiters;
	unsigned int	start;
	char			*result;

	delimiters = 0;
	start = *startindex;
	wordlen = findlen(s, c, startindex, &delimiters);
	result = ft_substr(s, start + delimiters, wordlen);
	if (!result)
		return (NULL);
	return (result);
}

static void	freemem(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		result[i] = NULL;
		i++;
	}
	free(result);
	result = NULL;
}

char	**ft_split(char const *s, char c)
{
	unsigned int	words;
	unsigned int	startindex;
	unsigned int	i;
	char			**result;

	if (!s)
		return (NULL);
	words = countword(s, c);
	result = malloc((1 + words) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	startindex = 0;
	result[words] = NULL;
	while (i < words)
	{
		result[i] = allocwords(s, c, &startindex);
		if (!result[i])
		{
			freemem(result);
			return (NULL);
		}
		i++;
	}
	return (result);
}
