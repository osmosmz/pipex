/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:19:54 by mzhuang           #+#    #+#             */
/*   Updated: 2024/07/28 19:56:21 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h> // comment away after

void	cleanup(t_cmd *cmds, int totalcommands, int *fds, int type)
{
	freecmds(cmds, totalcommands);
	close(fds[STDIN_FILENO]);
	close(fds[STDOUT_FILENO]);
	if (type == EXIT_FAILURE)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(type);
	}
	else
		exit(type);
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

void	getbin(t_cmd *comd, char **path)
{
	char	*actualpath;
	char	*pathwithslash;

	comd->bin = NULL;
	while (*path)
	{
		pathwithslash = ft_strjoin(*path, "/");
		actualpath = ft_strjoin(pathwithslash, comd->argv[0]);
		free(pathwithslash);
		if (access(actualpath, F_OK))
		{
			comd->bin = actualpath;
			break ;
		}
		else
			free(actualpath);
		path++;
	}
	if (!(comd->bin))
	{
		ft_printf(strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	parsecmds(t_cmd *cmds, char **envp, char **av, int totalcommands)
{
	char	**path;
	int		i;

	path = parsepath(envp);
	i = 0;
	while (i < totalcommands)
	{
		cmds[i].cmdnumber = i + 1;
		cmds[i].fdin = -1;
		cmds[i].fdout = -1;
		cmds[i].argv = ft_split(av[cmds[i].cmdnumber + 1], ' ');
		getbin(cmds + i, path);
		i++;
	}
	freepath(path);
}

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

int	createpipe(int pipefd[][2], int totalpipes)
{
	int	i;

	i = 0;
	while (i < totalpipes)
	{
		if (pipe(pipefd[i]) < 0)
		{
			ft_putstr_fd("Pipe:", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < totalpipes)
	{
		ft_printf("PipeIN:%i\n", pipefd[i][0]); // rem to remove
		ft_printf("PipeIN:%i\n", pipefd[i][1]); // rem to remove
		i++;
	}
	return (EXIT_SUCCESS);
}

void	allocatepipefd(t_cmd *cmds, int pipefd[][2])
{
	if (cmds->fdin == -1)
		cmds->fdin = pipefd[cmds->cmdnumber - 2][0];
	if (cmds->fdout == -1)
		cmds->fdout = pipefd[cmds->cmdnumber - 1][1];
	dup2(cmds->fdin, 0);
	dup2(cmds->fdout, 1);
	close(cmds->fdin);
	close(cmds->fdout);
}

void	closefds(int pipefd[][2], int totalpipes)
{
	int	i;

	i = 0;
	while (i < totalpipes)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}

int	pipex(t_cmd *cmds, int totalcmds,char **envp)
{
	int		i;
	int		pipefd[totalcmds - 1][2];
	pid_t	pid;

	i = 0;
	if (createpipe(pipefd, totalcmds - 1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (i < totalcmds)
	{
		pid = fork();
		if (pid < 0)
		{
			ft_putstr_fd("Fork:", 2);
			return (EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			allocatepipefd(cmds + i, pipefd);
			//	closefds(pipefd, totalcmds - 1);
			execve(cmds[i].bin, cmds[i].argv, envp);
			ft_putstr_fd("Execve:", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	closefds(pipefd, totalcmds - 1);
	for (int i = 0; i < totalcmds; ++i)
	{
		wait(NULL);
	}
	return (EXIT_SUCCESS);
}

void	printstruct(t_cmd *cmds, int totalcommands)
{
	int	i;
	int	j;

	i = 0;
	while (i < totalcommands)
	{
		ft_printf("cmds %i", cmds[i].cmdnumber);
		j = 0;
		while (cmds[i].argv[j])
		{
			ft_printf(cmds[i].argv[j]);
			j++;
		}
		ft_printf("\n");
		ft_printf(cmds[i].bin);
		i++;
	}
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

void	openfiles(int *fds, char **av, int ac)
{
	if (ac < 5)
	{
		ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile");
		exit(EXIT_FAILURE);
	}
	fds[STDIN_FILENO] = open(av[1], O_RDONLY);
	if (fds[STDIN_FILENO] < 0)
	{
		ft_printf("%s: %s\n", av[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	fds[STDOUT_FILENO] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fds[STDOUT_FILENO] < 0)
	{
		ft_printf("%s: %s\n", av[ac - 1], strerror(errno));
		close(fds[STDIN_FILENO]);
		exit(EXIT_FAILURE);
	}
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

int	main(int ac, char **av, char **envp)
{
	int		fds[2];
	t_cmd	*cmds;
	int		totalcommands;

	openfiles(fds, av, ac);
	totalcommands = ac - OTHER_AC;
	cmds = malloc(sizeof(t_cmd) * totalcommands);
	if (!cmds)
		cleanup(cmds, totalcommands, fds, EXIT_FAILURE);
	parsecmds(cmds, envp, av, totalcommands);
	updatefds(cmds, fds, totalcommands);
	if (pipex(cmds, totalcommands,envp) == EXIT_FAILURE)
		cleanup(cmds, totalcommands, fds, EXIT_FAILURE);
	// printstruct(cmds, totalcommands);
	cleanup(cmds, totalcommands, fds, EXIT_SUCCESS);
}
