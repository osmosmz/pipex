/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:10:39 by mzhuang           #+#    #+#             */
/*   Updated: 2024/08/18 17:25:26 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipecleanup(t_cmd *cmds, t_context *ctx, int type, int printmessage)
{
	closefds(ctx->fds);
	closefds(ctx->pipefd);
	if (ctx->heredoc)
		unlink(ctx->av[1]);
	if (ctx->heredoc && ft_strncmp(ctx->av[1], "here_doc", 9) != 0)
		free(ctx->av[1]);
	freecmds(cmds, ctx->totalcommands);
	free(ctx->pid);
	if (type == EXIT_FAILURE && printmessage == PRINTERRORMSG)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(type);
	}
	else
		exit(type);
}

void	freecmds(t_cmd *cmds, int totalcommands)
{
	int	i;
	int	j;

	if (!cmds)
		return ;
	i = 0;
	while (i < totalcommands)
	{
		if (cmds[i].bin)
			free(cmds[i].bin);
		if (cmds[i].argv)
		{
			j = 0;
			while (cmds[i].argv[j])
			{
				free(cmds[i].argv[j]);
				j++;
			}
			free(cmds[i].argv);
		}
		i++;
	}
	free(cmds);
}

void	closefds(int *fds)
{
	if (fds[STDIN_FILENO] != -1)
		close(fds[STDIN_FILENO]);
	if (fds[STDOUT_FILENO] != -1)
		close(fds[STDOUT_FILENO]);
}

void	freepath(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}
