/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:47:54 by mzhuang           #+#    #+#             */
/*   Updated: 2024/05/19 11:03:43 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Function name ft_putendl_fd
// Prototype void ft_putendl_fd(char *s, int fd);
// Turn in files -
// Parameters s: The string to output.
// fd: The file descriptor on which to write.
// Return value None
// External functs. write
// Description Outputs the string ’s’ to the given file descriptor
// followed by a newline.

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
