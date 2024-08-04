/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:19:54 by mzhuang           #+#    #+#             */
/*   Updated: 2024/08/03 18:24:00 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (dup2(cmds->fdin, 0) != -1)
		close(cmds->fdin);
	if (dup2(cmds->fdout, 1) != -1)
		close(cmds->fdout);
	return (EXIT_SUCCESS);
}

void	executecmd(t_cmd *cmds, t_cmd *curcmd, int totalcmds, char **envp)
{
	if (curcmd->fdin == -1 || curcmd->fdout == -1)
		cleanup(cmds, totalcmds, EXIT_FAILURE, SKIPERRORMSG);
	if (!curcmd->bin)
		cleanup(cmds, totalcmds, 127, SKIPERRORMSG);
	if (execve(curcmd->bin, curcmd->argv, envp) == -1)
	{
		ft_putstr_fd("execve", 2);
		cleanup(cmds, totalcmds, EXIT_FAILURE, SKIPERRORMSG);
	}
}

int	pipex(t_cmd *cmds, int totalcmds, char **envp, int *status)
{
	int		i;
	int		pipefd[2];
	pid_t	*pid;

	i = -1;
	pid = malloc(sizeof(pid_t) * totalcmds);
	if (!pid)
		return (EXIT_FAILURE);
	while (++i < totalcmds)
	{
		if (createpipe(pipefd, cmds + i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		pid[i] = fork();
		if (pid[i] < 0)
			return (EXIT_FAILURE);
		else if (pid[i] == 0)
			executecmd(cmds, cmds + i, totalcmds, envp);
	}
	i = -1;
	while (++i < totalcmds)
	{
		if (waitpid(pid[i], status, 0) == -1)
			return (EXIT_FAILURE);
	}
	return (free(pid), EXIT_SUCCESS);
}

void	openfiles(int *fds, char **av, int ac)
{
	if (ac != 5)
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

int	main(int ac, char **av, char **envp)
{
	int		fds[2];
	t_cmd	*cmds;
	int		totalcommands;
	int		status;

	status = EXIT_FAILURE;
	openfiles(fds, av, ac);
	totalcommands = ac - OTHER_AC;
	cmds = malloc(sizeof(t_cmd) * totalcommands);
	if (!cmds)
	{
		closefds(fds);
		cleanup(cmds, totalcommands, EXIT_FAILURE, PRINTERRORMSG);
	}
	parsecmds(cmds, envp, av, totalcommands);
	updatefds(cmds, fds, totalcommands);
	if (pipex(cmds, totalcommands, envp, &status) == EXIT_FAILURE)
		cleanup(cmds, totalcommands, EXIT_FAILURE, PRINTERRORMSG);
	status = WEXITSTATUS(status);
	cleanup(cmds, totalcommands, status, SKIPERRORMSG);
}
