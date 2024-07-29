/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:20:08 by mzhuang           #+#    #+#             */
/*   Updated: 2024/07/29 20:16:16 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

# define OTHER_AC 3

typedef struct s_cmd
{
	char	*bin;
	char	**argv;
	int		cmdnumber;
	int		fdin;
	int		fdout;

}			t_cmd;

char		**parsepath(char **envp);
void		freecmds(t_cmd *cmds, int totalcommands);

#endif
