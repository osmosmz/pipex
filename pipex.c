/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:19:54 by mzhuang           #+#    #+#             */
/*   Updated: 2024/07/20 18:47:12 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		ft_printf("Usage: ./pipex infile cmd1 cmd2 ... outfile");
		return (1);
	}
	int readfd;
	int savefd;
	readfd = open(argv[1], O_RDONLY);
	savefd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (readfd < 0 || savefd < 0 )
	char **

		return (0);
}