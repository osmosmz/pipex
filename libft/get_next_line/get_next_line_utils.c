/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:08:45 by mzhuang           #+#    #+#             */
/*   Updated: 2024/07/15 19:11:26 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen2(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
	}
	return (i);
}

int	checknewlineloc(const char *s, unsigned char c)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == c)
				return (i + 1);
			i++;
		}
	}
	return (-1);
}

char	*customjoin(char *s1, char const *s2)
{
	char	*result;
	size_t	t_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	t_len = ft_strlen2(s1) + ft_strlen2(s2);
	result = malloc(sizeof(char) * (1 + t_len));
	if (!result)
		return (NULL);
	while (s1 && s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	return (result);
}

char	*ft_substr2(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	if (len == 0)
		return (NULL);
	if (len > ft_strlen2(s) - start)
		len = ft_strlen2(s) - start;
	if (start > ft_strlen2(s))
		len = 0;
	result = malloc((sizeof(char)) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < (len) && s[start + i])
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
