/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:19:54 by mzhuang           #+#    #+#             */
/*   Updated: 2024/08/22 13:26:06 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	openfiles(t_context *ctx, t_cmd *cmd)
{
	if (cmd->cmdnumber == 1)
	{
		if (ctx->heredoc == 1)
			makeheredoc(ctx);
		else
			ctx->fds[0] = open(ctx->av[1], O_RDONLY);
		if (ctx->fds[0] < 0)
			perror(ctx->av[1]);
	}
	dup2(ctx->fds[0], 0);
	close(ctx->fds[0]);
	if (cmd->cmdnumber == ctx->totalcommands)
	{
		if (ctx->heredoc == 1)
			ctx->fds[1] = open(ctx->av[ctx->ac - 1],
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			ctx->fds[1] = open(ctx->av[ctx->ac - 1],
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (ctx->fds[1] < 0)
			perror(ctx->av[ctx->ac - 1]);
	}
	else
		createpipe(ctx);
	dup2(ctx->fds[1], 1);
	close(ctx->fds[1]);
}

int	executecmd(t_cmd *cmds, int i, t_context *ctx)
{
	ctx->pid[i] = fork();
	if (ctx->pid[i] < 0)
		return (EXIT_FAILURE);
	else if (ctx->pid[i] == 0)
	{
		if (ctx->fds[0] == -1 || ctx->fds[1] == -1)
			pipecleanup(cmds, ctx, EXIT_FAILURE, SKIPERRORMSG);
		if (!cmds[i].bin)
			pipecleanup(cmds, ctx, 127, PRINTERRORMSG);
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
	int	i;

	i = -1;
	while (++i < ctx->totalcommands)
	{
		openfiles(ctx, cmds + i);
		if (executecmd(cmds, i, ctx) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (waitpid(ctx->pid[ctx->totalcommands - 1], &ctx->status, 0) == -1)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < ctx->totalcommands - 1)
	{
wait(0); // this waiting still does not work properly
	}
	return (EXIT_SUCCESS);
}

void	initialisectx(t_context *ctx, int ac, char **av, char **envp)
{
	if (ac < 5)
	{
		ft_putendl_fd("Usage: ./pipex infile cmd1 cmd2 ... outfile", 2);
		exit(EXIT_FAILURE);
	}
	ctx->status = EXIT_FAILURE;
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		if (ac < 6)
		{
			ft_putstr_fd("Usage: ./pipex here_doc LIMITER ", 2);
			ft_putendl_fd("cmd1 cmd2 ... outfile", 2);
			exit(EXIT_FAILURE);
		}
		ctx->heredoc = 1;
	}
	else
		ctx->heredoc = 0;
	ctx->ac = ac;
	ctx->av = av;
	ctx->envp = envp;
	ctx->totalcommands = ac - OTHER_AC - ctx->heredoc;
	ctx->pid = malloc(sizeof(pid_t) * ctx->totalcommands);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd		*cmds;
	t_context	ctx;

	initialisectx(&ctx, ac, av, envp);
	if (!ctx.pid)
		return (EXIT_FAILURE);
	if (!envp[0] || !envp)
	{
		ft_putstr_fd("Error!No Env!\n", 2);
		return (EXIT_FAILURE);
	}
	cmds = malloc(sizeof(t_cmd) * ctx.totalcommands);
	if (!cmds)
	{
		closefds(ctx.fds);
		pipecleanup(cmds, &ctx, EXIT_FAILURE, PRINTERRORMSG);
	}
	parsecmds(cmds, &ctx);
	if (pipex(cmds, &ctx) == EXIT_FAILURE)
		pipecleanup(cmds, &ctx, EXIT_FAILURE, PRINTERRORMSG);
	ctx.status = WEXITSTATUS(ctx.status);
	pipecleanup(cmds, &ctx, ctx.status, SKIPERRORMSG);
}
