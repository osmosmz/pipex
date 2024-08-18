/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecommand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:03:12 by mzhuang           #+#    #+#             */
/*   Updated: 2024/08/18 22:53:02 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parsepath(char **envp)
{
	int	i;

	i = 0;
	if (envp)
	{
		while (envp[i])
		{
			if (ft_strnstr(envp[i], "PATH", 4))
				return (ft_split(&envp[i][5], ':'));
			i++;
		}
	}
	return (NULL);
}

void	getbin(t_cmd *comd, char **path)
{
	char	*actualpath;
	char	*pathwithslash;

	if (comd->argv[0] && ft_strchr(comd->argv[0], '/'))
	{
		if (access(comd->argv[0], F_OK) != -1)
			comd->bin = ft_strdup(comd->argv[0]);
	}
	else if (comd->argv[0] && path)
	{
		while (*path)
		{
			pathwithslash = ft_strjoin(*path, "/");
			actualpath = ft_strjoin(pathwithslash, comd->argv[0]);
			free(pathwithslash);
			if (access(actualpath, F_OK) != -1)
				comd->bin = actualpath;
			if (access(actualpath, F_OK) != -1)
				break ;
			free(actualpath);
			path++;
		}
	}
}

void	parsecmds(t_cmd *cmds, t_context *ctx)
{
	char	**path;
	int		i;

	path = parsepath(ctx->envp);
	i = 0;
	while (i < ctx->totalcommands)
	{
		cmds[i].bin = NULL;
		cmds[i].cmdnumber = i + 1;
		updatefds(cmds, i, ctx);
		cmds[i].argv = ft_split(ctx->av[cmds[i].cmdnumber + ctx->heredoc + 1],
				' ');
		getbin(cmds + i, path);
		if (!(cmds[i].bin) && cmds[i].fdin != -1 && cmds[i].fdout != -1)
		{
			if (cmds[i].argv[0])
				ft_putstr_fd(cmds[i].argv[0], 2);
			ft_putendl_fd(":command not found", 2);
		}
		i++;
	}
	freepath(path);
}

int	createpipe(t_context *ctx, t_cmd *cmds)
{
	if (cmds->fdin == UNINITIALISED)
		cmds->fdin = ctx->pipefd[0];
	if (pipe(ctx->pipefd) < 0)
	{
		ft_putstr_fd("Pipe:", 2);
		return (EXIT_FAILURE);
	}
	if (cmds->fdout == UNINITIALISED)
		cmds->fdout = ctx->pipefd[1];
	if (dup2(cmds->fdin, 0) != -1)
		close(cmds->fdin);
	if (dup2(cmds->fdout, 1) != -1)
		close(cmds->fdout);
	return (EXIT_SUCCESS);
}

void	updatefds(t_cmd *cmds, int i, t_context *ctx)
{
	if (cmds[i].cmdnumber == 1)
		cmds[i].fdin = ctx->fds[STDIN_FILENO];
	else
		cmds[i].fdin = UNINITIALISED;
	if (cmds[i].cmdnumber == ctx->totalcommands)
		cmds[i].fdout = ctx->fds[STDOUT_FILENO];
	else
		cmds[i].fdout = UNINITIALISED;
}
