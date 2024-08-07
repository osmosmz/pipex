/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:20:08 by mzhuang           #+#    #+#             */
/*   Updated: 2024/08/03 16:36:21 by mzhuang          ###   ########.fr       */
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

void		closefds(int *fds);
void		cleanup(t_cmd *cmds, int totalcommands, int type, int printmessage);
void		freecmds(t_cmd *cmds, int totalcommands);

char		**parsepath(char **envp);
void		getbin(t_cmd *comd, char **path);
void		freepath(char **path);
void		parsecmds(t_cmd *cmds, char **envp, char **av, int totalcommands);
void		updatefds(t_cmd *cmds, int *fds, int totalcommands);

#endif
