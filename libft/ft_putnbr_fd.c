/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:25:10 by mzhuang           #+#    #+#             */
/*   Updated: 2024/05/19 16:20:42 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Function name ft_putnbr_fd
// Prototype void ft_putnbr_fd(int n, int fd);
// Turn in files -
// Parameters n: The integer to output.
// fd: The file descriptor on which to write.
// Return value None
// External functs. write
// Outputs the integer ’n’ to the given file
// descriptor.

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}
