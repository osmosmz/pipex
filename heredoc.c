/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:52:02 by mzhuang           #+#    #+#             */
/*   Updated: 2024/08/04 13:41:25 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	makeheredoc(t_context *ctx)
{
	char	*buf;

	ctx->fds[0] = open(ctx->av[1], O_CREAT, O_RDONLY);
	ctx->fds[1] = open(ctx->av[ctx->ac - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	while (1)
	{
		buf = get_next_line(0);
		if (ft_strncmp(buf, ctx->av[2], ft_strlen(buf)) == 0)
			break ;
		write(ctx->fds[STDIN_FILENO], buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
}
