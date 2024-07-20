/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:03:29 by mzhuang           #+#    #+#             */
/*   Updated: 2024/07/20 12:50:53 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define NEWLINE '\n'

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
size_t	ft_strlen2(const char *s);
int		checknewlineloc(const char *s, unsigned char c);
char	*customjoin(char *s1, char const *s2);
char	*ft_substr2(char const *s, unsigned int start, size_t len);

#endif