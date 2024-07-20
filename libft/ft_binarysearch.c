/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binarysearch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:43:15 by mzhuang           #+#    #+#             */
/*   Updated: 2024/07/09 21:43:21 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_binarysearch(long *arrangednum, long searchitem, int left, int right)
{
	int	mid;

	if (left > right)
		return (-1);
	mid = left + (right - left) / 2;
	if (arrangednum[mid] == searchitem)
		return (mid);
	else if (arrangednum[mid] > searchitem)
		return (ft_binarysearch(arrangednum, searchitem, left, mid - 1));
	else
		return (ft_binarysearch(arrangednum, searchitem, mid + 1, right));
}
