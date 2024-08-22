/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecommand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:03:12 by mzhuang           #+#    #+#             */
/*   Updated: 2024/08/22 12:58:09 by mzhuang          ###   ########.fr       */
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
		// updatefds(cmds, i, ctx);
		cmds[i].argv = ft_split(ctx->av[cmds[i].cmdnumber + ctx->heredoc + 1],
				' ');
		getbin(cmds + i, path);
		// if (!(cmds[i].bin) && cmds[i].fdin != -1 && cmds[i].fdout != -1)
		// {
		// 	if (cmds[i].argv[0])
		// 		ft_putstr_fd(cmds[i].argv[0], 2);
		// 	ft_putendl_fd(":command not found", 2);
		// }
		i++;
	}
	freepath(path);
}

void	createpipe(t_context *ctx)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
	{
		ft_putstr_fd("Create pipe error", 2);
		exit(EXIT_FAILURE);
	}
	ctx->fds[0] = pipefd[0];
	ctx->fds[1] = pipefd[1];
}
