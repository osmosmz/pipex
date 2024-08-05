/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:19:54 by mzhuang           #+#    #+#             */
/*   Updated: 2024/08/05 21:07:43 by mzhuang          ###   ########.fr       */
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

int	executecmd(t_cmd *cmds, int i, pid_t *pid, t_context *ctx)
{
	pid[i] = fork();
	if (pid[i] < 0)
		return (EXIT_FAILURE);
	else if (pid[i] == 0)
	{
		if (cmds[i].fdin == -1 || cmds[i].fdout == -1)
			pipecleanup(cmds, ctx, EXIT_FAILURE, SKIPERRORMSG);
		if (!cmds[i].bin)
			pipecleanup(cmds, ctx, 127, SKIPERRORMSG);
		if (execve(cmds[i].bin, cmds[i].argv, ctx->envp) == -1)
		{
			ft_putstr_fd("execve", 2);
			pipecleanup(cmds, ctx, EXIT_FAILURE, SKIPERRORMSG);
		}
	}
	return (EXIT_SUCCESS);
}

int	pipex(t_cmd *cmds, t_context *ctx)
{
	int		i;
	int		pipefd[2];
	pid_t	*pid;

	i = -1;
	pid = malloc(sizeof(pid_t) * ctx->totalcommands);
	if (!pid)
		return (EXIT_FAILURE);
	while (++i < ctx->totalcommands)
	{
		if (createpipe(pipefd, cmds + i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (executecmd(cmds, i, pid, ctx) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	i = -1;
	while (++i < ctx->totalcommands)
	{
		if (waitpid(pid[i], &ctx->status, 0) == -1)
			return (EXIT_FAILURE);
	}
	free(pid);
	return (EXIT_SUCCESS);
}

void	openfiles(t_context *ctx)
{
	if (ctx->heredoc == 1)
	{
		if (ctx->ac < 6)
		{
			ft_printf("Usage: ./pipex here_doc LIMITER cmd1 cmd2 ... outfile");
			exit(EXIT_FAILURE);
		}
		makeheredoc(ctx);
	}
	else
	{
		if (ctx->ac < 5)
		{
			ft_printf("Usage: ./pipex infile cmd1 cmd2 ... outfile");
			exit(EXIT_FAILURE);
		}
		ctx->fds[0] = open(ctx->av[1], O_RDONLY);
		ctx->fds[1] = open(ctx->av[ctx->ac - 1], O_CREAT | O_RDWR | O_TRUNC,
				0644);
	}
	if (ctx->fds[0] < 0)
		perror(ctx->av[1]);
	if (ctx->fds[1] < 0)
		perror(ctx->av[ctx->ac - 1]);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd		*cmds;
	t_context	ctx;

	ctx.status = EXIT_FAILURE;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		ctx.heredoc = 1;
	else
		ctx.heredoc = 0;
	ctx.ac = ac;
	ctx.av = av;
	ctx.envp = envp;
	ctx.totalcommands = ac - OTHER_AC - ctx.heredoc;
	openfiles(&ctx);
	cmds = malloc(sizeof(t_cmd) * ctx.totalcommands);
	if (!cmds)
	{
		closefds(ctx.fds);
		pipecleanup(cmds, &ctx, EXIT_FAILURE, PRINTERRORMSG);
	}
	parsecmds(cmds, &ctx);
	updatefds(cmds, &ctx);
	if (pipex(cmds, &ctx) == EXIT_FAILURE)
		pipecleanup(cmds, &ctx, EXIT_FAILURE, PRINTERRORMSG);
	ctx.status = WEXITSTATUS(ctx.status);
	pipecleanup(cmds, &ctx, ctx.status, SKIPERRORMSG);
}
