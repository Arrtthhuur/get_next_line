/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gnl_test.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 15:45:55 by abeznik       #+#    #+#                 */
/*   Updated: 2020/12/02 16:31:01 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		gnl_check_nl(char *save)
{
	int				len;
	
	len = 0;
	while (save[len] != '\0')
	{
		if (save[len] == '\n')
			return (len);
		len++;
	}
	return (-1);
}

int		gnl_ret_line(char **save, char **line, int len)
{
	char			*tmp;

	*line = ft_substr(*save, 0, len);
	tmp = ft_strdup(&(*save)[len + 1]);
	free(*save);
	*save = tmp;
	return (1);
}

int		gnl_ret_rest(char **save, char **line)
{
	int				len;

	if (*save == 0)
	{
		*line = ft_strdup("");
		return (0);
	}
	len = gnl_check_nl(*save);
	if (*save && (len >= 0))
		return (gnl_ret_line(save, line, len));
	else if (*save[0] != '\0')
	{
		*line = ft_strdup(*save);
		free(*save);
		*save = 0;
		return (0);
	}
	*line = ft_strdup("");
	free(*save);
	*save = 0;
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int				len;
	size_t			nbytes;
	char			buffer[BUFFER_SIZE + 1];
	static char		*save[4096];

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
	{
		printf("fd = %d, line = %s & BUFFER_SIZE = %d\n", fd, *line, BUFFER_SIZE);
		return (-1);
	}
	while ((nbytes = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[nbytes] = '\0';
		save[fd] = gnl_strjoin(save[fd], buffer);
		 
		len = gnl_check_nl(save[fd]);
		if (len >= 0)
			return(gnl_ret_line(&save[fd], line, len));
	}
	if (nbytes < 0)
		return (-1);
	return (gnl_ret_rest(&save[fd], line));
}