/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:26:53 by mzhuang           #+#    #+#             */
/*   Updated: 2024/05/15 20:27:02 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// returns 0 if not alpha, else is alpha return any other value

static int	ft_islower(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (1);
	}
	return (0);
}

static int	ft_isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (1);
	}
	return (0);
}

int	ft_isalpha(int c)
{
	return (ft_islower(c) || ft_isupper(c));
}
