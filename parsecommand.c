/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecommand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:03:12 by mzhuang           #+#    #+#             */
/*   Updated: 2024/08/03 17:24:04 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parsepath(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			return (ft_split(&envp[i][5], ':'));
		i++;
	}
	return (NULL);
}

void	getbin(t_cmd *comd, char **path)
{
	char	*actualpath;
	char	*pathwithslash;

	if (comd->argv[0])
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
			else
				free(actualpath);
			path++;
		}
	}
	if (!(comd->bin))
	{
		if (comd->argv[0])
			ft_putstr_fd(comd->argv[0], 2);
		ft_putendl_fd("command not found", 2);
	}
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

void	parsecmds(t_cmd *cmds, char **envp, char **av, int totalcommands)
{
	char	**path;
	int		i;

	path = parsepath(envp);
	i = 0;
	while (i < totalcommands)
	{
		cmds[i].bin = NULL;
		cmds[i].cmdnumber = i + 1;
		cmds[i].fdin = -5;
		cmds[i].fdout = -5;
		cmds[i].argv = ft_split(av[cmds[i].cmdnumber + 1], ' ');
		getbin(cmds + i, path);
		i++;
	}
	freepath(path);
}

void	updatefds(t_cmd *cmds, int *fds, int totalcommands)
{
	int	i;

	i = 0;
	while (i < totalcommands)
	{
		if (cmds[i].cmdnumber == 1)
			cmds[i].fdin = fds[STDIN_FILENO];
		if (cmds[i].cmdnumber == totalcommands)
			cmds[i].fdout = fds[STDOUT_FILENO];
		i++;
	}
}
