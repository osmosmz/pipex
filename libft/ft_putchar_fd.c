/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:06:56 by mzhuang           #+#    #+#             */
/*   Updated: 2024/05/17 19:00:02 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Function name ft_putchar_fd
// Prototype void ft_putchar_fd(char c, int fd);
// Turn in files -
// Parameters c: The character to output.
// fd: The file descriptor on which to write.
// Return value None
// External functs. write
// Description Outputs the character ’c’ to the given file
// descriptor.

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
