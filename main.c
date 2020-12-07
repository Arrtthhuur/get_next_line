/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/16 11:16:37 by abeznik       #+#    #+#                 */
/*   Updated: 2020/12/07 16:02:13 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int			main(void)
{
	char	*line;
	int		fd;
	int		line_nb;
	int		ret;

	fd = open("test2.txt", O_RDONLY);
	line_nb = 1;
	ret = 0;
	while ((ret = get_next_line(fd, &line)))
	{
		printf("\033[1;31m");
		printf("Line #%d:	%s\n", line_nb, line);
		printf("\033[0m");
		free(line);
		line_nb++;
	}
	printf("\033[1;31m");
	printf("get_next_line returned %d", ret);
	printf("\nRead whole file!\n");
	printf("\033[0m");
	return (0);
}
