/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:19:54 by mzhuang           #+#    #+#             */
/*   Updated: 2024/07/21 16:12:39 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h> // comment away after

char *parsepath(char **envp)
{	
	char *result;
	int i;
	i=0;
	while (envp[i])
	{
		if(ft_substr())
		i++;
	}

}



int	main(int argc, char **argv, char **envp)
{
	(void) argc ;
	(void) argv;
	// if (argc < 5)
	// {
	// 	ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile");
	// 	return (1);
	// }
	// int readfd;
	// int savefd;

	// char * string;
	while (envp)
	{
		printf("%s\n", *envp);
		envp++;
	}

	// readfd = open(argv[1], O_RDONLY);
	// savefd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	// if (readfd < 0 || savefd < 0 )
}