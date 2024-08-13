/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:52:02 by mzhuang           #+#    #+#             */
/*   Updated: 2024/08/13 22:38:11 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	makeheredoc(t_context *ctx)
{
	char	*buf;

	ctx->fds[0] = open(ctx->av[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ctx->fds[1] = open(ctx->av[ctx->ac - 1], O_CREAT | O_WRONLY | O_APPEND,
			0644);
	if (ctx->fds[0] < 0)
		perror(ctx->av[1]);
	if (ctx->fds[1] < 0)
		perror(ctx->av[ctx->ac - 1]);
	while (1)
	{
		buf = get_next_line(0);
		if (ft_strncmp(buf, ctx->av[2], ft_strlen(ctx->av[2])) == 0)
			break ;
		write(ctx->fds[0], buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(ctx->fds[0]);
	ctx->fds[0] = open(ctx->av[1], O_RDONLY);
	if (ctx->fds[0] < 0)
		perror(ctx->av[1]);
}
