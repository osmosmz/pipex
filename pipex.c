/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:19:54 by mzhuang           #+#    #+#             */
/*   Updated: 2024/07/26 01:38:11 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h> // comment away after


void parsecmds(t_cmd *cmds, char **envp, char**av)
{
	// todo
}
char	*parsepath(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			return (ft_strdup(envp[i]));
		i++;
	}
	return (NULL);
}

// parser function to inintialise all cmds
// cmds is a struct with cmd number (1,2,3 etc)
// its cmd args
// its bin

char	*getpaths(char **envp, char **argv, int cmdno)
{
	char	*path;
	char	**paths;
	char	**cmdargs;
	char	*finalpath;
	char	*bin;

	path = parsepath(envp);
	paths = ft_split(&path[5], ':');
	cmdargs = ft_split(argv[cmdno + 1], ' ');
	free(path);
	while (*paths)
	{
		finalpath = ft_strjoin(*paths, "/");
		bin = ft_strjoin(finalpath, cmdargs[0]);
		free(finalpath);
		if (access(bin, F_OK))
			return (bin);
		(paths)++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_cmd cmds[2];
	if (argc < 5)
	{
		ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile");
		return (1);
	}
	parsecmds(cmds,envp,argv);
	// int readfd;
	// int savefd;
	// readfd = open(argv[1], O_RDONLY);
	// savefd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	getpaths(envp, argv, 1);
	// while (envp)
	// {
	// 	printf("%s\n", *envp);
	// 	envp++;
	// }

	// if (readfd < 0 || savefd < 0 )
}