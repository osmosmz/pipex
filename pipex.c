/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:19:54 by mzhuang           #+#    #+#             */
/*   Updated: 2024/08/02 02:18:17 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h> // comment away after

void	cleanup(t_cmd *cmds, int totalcommands, int *fds, int type)
{
	freecmds(cmds, totalcommands);
	if (fds)
	{
		close(fds[STDIN_FILENO]);
		close(fds[STDOUT_FILENO]);
	}
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
		if (access(actualpath, F_OK) != -1)
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
		ft_printf("%s: %s\n", comd->argv[0], "command not found");
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
		cmds[i].fdin = -5;
		cmds[i].fdout = -5;
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

int	createpipe(int *pipefd, t_cmd *cmds)
{
	if (cmds->fdin == -5)
		cmds->fdin = pipefd[0];
	if (pipe(pipefd) < 0)
	{
		ft_putstr_fd("Pipe:", 2);
		return (EXIT_FAILURE);
	}
	if (cmds->fdout == -5)
		cmds->fdout = pipefd[1];
	dup2(cmds->fdin, 0);
	close(cmds->fdin);
	dup2(cmds->fdout, 1);
	close(cmds->fdout);
	return (EXIT_SUCCESS);
}

int	pipex(t_cmd *cmds, int totalcmds, char **envp, int *status)
{
	int		i;
	int		pipefd[2];
	pid_t	pid[totalcmds];

	*status = EXIT_FAILURE;
	i = 0;
	while (i < totalcmds)
	{
		if (createpipe(pipefd, cmds + i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		pid[i] = fork();
		if (pid[i] < 0)
		{
			ft_putstr_fd("Fork:", 2);
			return (EXIT_FAILURE);
		}
		else if (pid[i] == 0)
		{
			if (cmds[i].fdin == -1 || cmds[i].fdout == -1)
				exit(EXIT_FAILURE);
			if (!cmds[i].bin)
			{
				ft_putstr_fd("argv[0]", 2);
				ft_putendl_fd("command not found", 2);
				cleanup(cmds, totalcmds, NULL, 127);
			}
			if (execve(cmds[i].bin, cmds[i].argv, envp) == -1)
			{
				ft_putstr_fd("execve", 2);
				cleanup(cmds, totalcmds, NULL, EXIT_FAILURE);
			}
		}
		i++;
	}
	i = -1;
	while (++i < totalcmds)
	{
		if (waitpid(pid[i], status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
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
		perror(av[1]);
	fds[STDOUT_FILENO] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fds[STDOUT_FILENO] < 0)
		perror(av[ac - 1]);
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
	int		status;

	openfiles(fds, av, ac);
	totalcommands = ac - OTHER_AC;
	cmds = malloc(sizeof(t_cmd) * totalcommands);
	if (!cmds)
		cleanup(cmds, totalcommands, fds, EXIT_FAILURE);
	parsecmds(cmds, envp, av, totalcommands);
	updatefds(cmds, fds, totalcommands);
	if (pipex(cmds, totalcommands, envp, &status) == EXIT_FAILURE)
		cleanup(cmds, totalcommands, fds, EXIT_FAILURE);
	status = WEXITSTATUS(status);
	// printstruct(cmds, totalcommands);
	cleanup(cmds, totalcommands, fds, status);
}
