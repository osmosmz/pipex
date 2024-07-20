/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:21:26 by mzhuang           #+#    #+#             */
/*   Updated: 2024/07/08 22:45:33 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// function that takes in the int and base and returns in the baseformat

#include "libft.h"

static int	checkduplicates(const char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		j = 0;
		while (j < i)
		{
			if (base[j] == base[i])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	ft_getnumdigits(int n, int *sign, int baselength)
{
	int	len;

	if (n == 0)
		return (1);
	else if (n < 0)
	{
		(*sign)++;
		n /= baselength;
		n *= -1;
		len = 1;
	}
	else
		len = 0;
	while (n > 0)
	{
		n /= baselength;
		len++;
	}
	return (len);
}

static unsigned int	ft_abs(int n)
{
	if (n < 0)
		return ((unsigned int)-n);
	else
		return (n);
}

char	*ft_itoabase(int n, const char *base)
{
	int				len;
	char			*result;
	unsigned int	postive_n;
	int				sign;
	int				baselength;

	baselength = ft_strlen(base);
	if (!baselength || !checkduplicates(base))
		return (ft_strdup(""));
	sign = 0;
	len = ft_getnumdigits(n, &sign, baselength);
	result = malloc(sizeof(char) * (len + sign + 1));
	if (!result)
		return (NULL);
	if (sign)
		result[0] = '-';
	result[len + sign] = '\0';
	postive_n = ft_abs(n);
	while (len > 0)
	{
		result[len + sign - 1] = base[postive_n % baselength];
		postive_n /= baselength;
		len--;
	}
	return (result);
}
