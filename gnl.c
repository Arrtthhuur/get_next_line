/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gnl.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/30 18:10:48 by abeznik       #+#    #+#                 */
/*   Updated: 2020/12/01 15:52:22 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
ft_strchr - yellow 
*/
char			*ft_strchr(const char *s, int c)
{
	printf("\033[1;33m");
	printf("String to be searched: \n[%s]\n", s);
	while (*s != (char)c && *s != 0)
	{
		printf("Char: \n%c\n", *s);
		s++;
	}
	if (*s == (char)c)
	{
		printf("EOL found\n");
		printf("Return string after EOL [%s]\n", s);
		return ((char*)s);
	}
	else
	{
		printf("No EOL found\n");
		return (NULL);
	}
	printf("No EOL found\n");
	printf("\033[0m");
	return (NULL);
}

/*
ft_clean_line - blue
*/
char			*ft_clean_line(char *line_read, char **line, int nbytes)
{
	unsigned int	len;
	char			*tmp;

	printf("\033[1;36m");
	len = 0;
	while (line_read[len] != '\n' && line_read[len] != '\0')
	{
		printf("line_read[%d] = %c\n", len, line_read[len]);
		len++;
	}
	printf("EOL found at len: %d\n", len);
	printf("nbytes = 0 or len < len of line_read\n");
	if (nbytes == 0)
	{
		printf("nbytes = %d\n", nbytes);
		printf("\n"); 
		*line = line_read;
		printf("*line = [%s]\n", *line);
		printf("\n");
		line_read = NULL;
		printf("line_read = [%s]\n", line_read);
		printf("\n");
	}
	else if (len < ft_strlen(line_read))
	{
		printf("%d < %ld\n", len, ft_strlen(line_read));
		*line = ft_substr(line_read, 0, len);
		printf("Substr of [%s] from 0 to %d: *line = [%s]\n", line_read, len, *line);
		printf("\n");
		tmp = ft_substr(line_read, len + 1, ft_strlen(line_read));
		printf("Substr of [%s] from %d to %ld: tmp = [%s]\n", line_read, len + 1, ft_strlen(line_read), tmp);
		printf("\n");
		printf("line_read before free = [%s]\n", line_read);
		printf("\n");
		free(line_read);
		printf("free line_read = [%s]\n", line_read);
		printf("\n");
		line_read = ft_strdup(tmp);
		printf("Dup tmp to line_read = [%s]\n", line_read);
		printf("\n");
		printf("tmp before free = [%s]\n", tmp);
		printf("\n");
		free(tmp);
		printf("free tmp = [%s]\n", tmp);
		printf("\n");
	}
	printf("return line_read = [%s]\n", line_read);
	printf("\n");
	printf("\033[0m");
	return (line_read);
}

/*
ft_save - green
*/
char				*ft_save(char *buffer, char *line_read)
{
	char			*tmp;
	
	printf("\033[1;32m");
	if (line_read)
	{
		printf("Line_read not empty:\n[%s]\n", line_read);
		printf("\n");
		tmp = ft_strjoin(line_read, buffer);
		printf("Join line_read and buffer to tmp:\n[%s]\n", tmp);
		printf("\n");
		free(line_read);
		printf("Free line_read: [%s]\n", line_read);
		printf("\n");
		line_read = ft_strdup(tmp);
		printf("Duplicate tmp to line_read:\n[%s]\n", line_read);
		printf("\n");
		free(tmp);
		printf("Free tmp: [%s]\n", tmp);
		printf("\n");
	}
	else
	{
		printf("Line_read empty:\n[%s]\n", line_read);
		printf("\n");
		line_read = ft_strdup(buffer);
		printf("Duplicate buffer to line_read:\n[%s]\n", line_read);
		printf("\n");
	}
	printf("return line_read = \n[%s]\n", line_read);
	printf("\n");
	printf("\033[0m");
	return(line_read);
}

/*
get_next_line - magenta
*/
int				get_next_line(int fd, char **line)
{
	static char		*line_read[4096];
	char			buffer[BUFFER_SIZE + 1];
	int				nbytes;

	printf("\033[1;35m");
	while ((nbytes = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		printf("Read %d bytes\n", nbytes);
		if (nbytes == -1)
			return (-1);
		buffer[nbytes] = '\0';
		printf("Buffer in loop:\n[%s]\n", buffer);
		printf("\n");
		printf("Save buffer in static array\n");
		line_read[fd] = ft_save(buffer, line_read[fd]);
		printf("Search buffer for EOL\n");
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	printf("Broke the read loop!\n");
	printf("Read %d bytes\n", nbytes);
	if (nbytes <= 0 && !line_read[fd])
	{
		*line = ft_strdup("");
		return (nbytes);
	}
	printf("Sending [%s], line and %d to clean_line\n", line_read[fd], nbytes);
		printf("\n");

	line_read[fd] = ft_clean_line(line_read[fd], line, nbytes);
	printf("line_read[%d] = \n[%s]\n", fd, line_read[fd]);
	printf("\n");
	if (nbytes <= 0 && !line_read[fd])
		return (nbytes);
	printf("\033[0m");
	return (1);
}