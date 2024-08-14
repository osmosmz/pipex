/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:20:08 by mzhuang           #+#    #+#             */
/*   Updated: 2024/08/14 19:56:26 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

# define OTHER_AC 3
# define UNINITIALISED -2
# define PRINTERRORMSG 1
# define SKIPERRORMSG 0

typedef struct s_cmd
{
	char	*bin;
	char	**argv;
	int		cmdnumber;
	int		fdin;
	int		fdout;

}			t_cmd;

typedef struct s_context
{
	char	**av;
	char	**envp;
	int		ac;
	int		heredoc;
	int		totalcommands;
	int		fds[2];
	int		pipefd[2];
	int		status;
	pid_t	*pid;

}			t_context;

void		closefds(int *fds);
void		pipecleanup(t_cmd *cmds, t_context *ctx, int type,
				int printmessage);
void		freecmds(t_cmd *cmds, int totalcommands);
void		freepath(char **path);

char		**parsepath(char **envp);
void		getbin(t_cmd *comd, char **path);
void		parsecmds(t_cmd *cmds, t_context *ctx);
void		updatefds(t_cmd *cmds, t_context *ctx);
int			createpipe(t_context *ctx, t_cmd *cmds);

void		makeheredoc(t_context *ctx);

#endif
