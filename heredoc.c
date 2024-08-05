/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:52:02 by mzhuang           #+#    #+#             */
/*   Updated: 2024/08/05 20:59:42 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	makeheredoc(t_context *ctx)
{
	char	*buf;
	int		written;

	ctx->fds[0] = open(ctx->av[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	ctx->fds[1] = open(ctx->av[ctx->ac - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	while (1)
	{
		buf = get_next_line(0);
		if (ft_strncmp(buf, ctx->av[2], ft_strlen(ctx->av[2])) == 0)
			break ;
		written = write(ctx->fds[STDIN_FILENO], buf, ft_strlen(buf));
		printf("%i", written);
		free(buf);
	}
	free(buf);
}
