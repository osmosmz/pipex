/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:52:02 by mzhuang           #+#    #+#             */
/*   Updated: 2024/08/18 16:57:12 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	createfile(t_context *ctx)
{
	int		i;
	char	*suffix;
	char	*temp;

	i = 0;
	while (1)
	{
		ctx->fds[0] = open(ctx->av[1], O_RDONLY);
		if (ctx->fds[0] == -1)
			break ;
		close(ctx->fds[0]);
		suffix = ft_itoa(i);
		temp = ft_strjoin(ctx->av[1], suffix);
		if (i > 0)
			free(ctx->av[1]);
		ctx->av[1] = ft_strdup(temp);
		free(temp);
		free(suffix);
		i++;
	}
}

void	makeheredoc(t_context *ctx)
{
	char	*buf;

	createfile(ctx);
	ctx->fds[0] = open(ctx->av[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ctx->fds[1] = open(ctx->av[ctx->ac - 1], O_CREAT | O_WRONLY | O_APPEND,
			0644);
	while (1)
	{
		buf = get_next_line(0);
		if (!buf)
			break ;
		if (ft_strncmp(buf, ctx->av[2], ft_strlen(ctx->av[2]) + 1) == '\n')
			break ;
		write(ctx->fds[0], buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(ctx->fds[0]);
	ctx->fds[0] = open(ctx->av[1], O_RDONLY);
}
