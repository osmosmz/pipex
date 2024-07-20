/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:08:42 by mzhuang           #+#    #+#             */
/*   Updated: 2024/07/15 19:12:03 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*nextline(int fd, char *bufferbal)
{
	int		readbytes;
	char	*readdata;

	readdata = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!readdata)
		return (NULL);
	readbytes = 1;
	while (checknewlineloc(bufferbal, NEWLINE) == -1)
	{
		readbytes = read(fd, readdata, BUFFER_SIZE);
		if (readbytes == -1)
		{
			free(readdata);
			free(bufferbal);
			return (NULL);
		}
		if (readbytes == 0)
			break ;
		readdata[readbytes] = '\0';
		bufferbal = customjoin(bufferbal, readdata);
	}
	free(readdata);
	return (bufferbal);
}

char	*cleanup(char *buffer, const size_t strlen)
{
	size_t	i;
	size_t	balancelen;

	i = 0;
	balancelen = ft_strlen2(buffer) - strlen;
	if (!balancelen)
	{
		free(buffer);
		buffer = NULL;
	}
	else
	{
		while (i < balancelen)
		{
			buffer[i] = buffer[strlen + i];
			i++;
		}
		buffer[i] = '\0';
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024] = {NULL};
	char		*result;
	int			strlen;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = nextline(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	strlen = checknewlineloc(buffer[fd], NEWLINE);
	if (strlen == -1)
		strlen = ft_strlen2(buffer[fd]);
	result = ft_substr2(buffer[fd], 0, strlen);
	buffer[fd] = cleanup(buffer[fd], strlen);
	return (result);
}
