/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanups.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:10:39 by mzhuang           #+#    #+#             */
/*   Updated: 2024/08/03 16:27:33 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cleanup(t_cmd *cmds, int totalcommands, int type, int printmessage)
{
	freecmds(cmds, totalcommands);
	if (type == EXIT_FAILURE && printmessage == PRINTERRORMSG)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(type);
	}
	else
		exit(type);
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

void	closefds(int *fds)
{
	if (fds[STDIN_FILENO] != -1)
		close(fds[STDIN_FILENO]);
	if (fds[STDOUT_FILENO] != -1)
		close(fds[STDOUT_FILENO]);
}
