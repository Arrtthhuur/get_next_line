/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gnl_two.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/03 20:37:28 by abeznik       #+#    #+#                 */
/*   Updated: 2020/12/04 17:21:37 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void		ft_strdel(char **as)
{
	if (as)
	{
		free(*as);
		*as = NULL;
	}
	return ;
}

char		*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	if (*str == (char)c)
		return (str);
	i = 1;
	while (str[i - 1])
	{
		if (str[i] == (char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}

int		gnl_new_line(char **save, char **line)
{
	size_t			len;
	char			*tmp;

	len = 0;
	printf("Computing length of line\n");
	while ((*save)[len] != '\n' && (*save)[len] != '\0')
	{
		printf("(*save)[%ld] = %c\n", len, (*save)[len]);
		len++;
	}
	printf("EOL or EOF  found at len = %ld\n", len);
	printf("Checking if EOL or EOF...");
	if ((*save)[len] == '\n')
	{
		printf("Found EOL\n");
		*line = ft_substr(*save, 0, len);
		printf("\nSubstr of *save from 0 to %ld (pos. of EOL) to *line:", len);
		printf("\n\t\t*line\n");
		printf("-------------------------------------------\n");
		printf("[%s]\n", *line);
		printf("-------------------------------------------\n");
		printf("\n");
		tmp = ft_strdup(&((*save)[len + 1]));
		printf("\nDup of &(*save)[%ld] to tmp:", len + 1);
		printf("(Rest of save to be used later)");
		printf("\n\t\ttmp\n");
		printf("-------------------------------------------\n");
		printf("[%s]\n", tmp);
		printf("-------------------------------------------\n");
		printf("\n");
		free(*save);
		printf("\nFree *save");
		printf("\n\t\t*save\n");
		printf("-------------------------------------------\n");
		printf("[%s]\n", *save);
		printf("-------------------------------------------\n");
		printf("\n");
		*save = tmp;
		printf("\nAppend tmp to *save");
		printf("\n\t\t*save\n");
		printf("-------------------------------------------\n");
		printf("[%s]\n", *save);
		printf("-------------------------------------------\n");
		printf("\n");
		printf("Checking if (*save)[0] is EOL...");
		if ((*save)[0] == '\0')
		{
			printf("True\n");
			printf("Delete save\n");
			ft_strdel(save);
			printf("\n\t\tsave\n");
			printf("-------------------------------------------\n");
			printf("[%s]\n", *save);
			printf("-------------------------------------------\n");
			printf("\n");
		}
		printf("False\n");	
	}
	else if ((*save)[len] == '\0')
	{
		printf("Found EOF\n");
		*line = ft_strdup(*save);
		printf("\nDup of *save to *line:");
		printf("\n\t\t*line\n");
		printf("-------------------------------------------\n");
		printf("[%s]\n", *line);
		printf("-------------------------------------------\n");
		printf("\n");
		ft_strdel(save);
		printf("Delete save\n");
		printf("\n\t\tsave\n");
		printf("-------------------------------------------\n");
		printf("[%s]\n", *save);
		printf("-------------------------------------------\n");
		printf("\n");
	}
	printf("\033[1;36m");
	printf("\nReturn (1)! (Back to main)\n");
	printf("\033[0m");
	printf("\n");
	return (1);
}

int		gnl_check_ret(char **save, char **line, int nbytes, int fd)
{
	printf("Checking if return is...\n");
	printf("nbytes < 0 => (-1),\n");
	printf("nbytes == 0 && save[%d] == NULL => (0),\n", fd);
	printf("or send to gnl_new_line.\n");
	printf("nbytes = %d\nsave[%d] = [%s]\n", nbytes, fd, save[fd]);
	if (nbytes < 0)
	{
		printf("nbytes (%d) < 0... Return (-1)\n", nbytes);
		return (-1);
	}
	else if (nbytes == 0 && save[fd] == NULL)
	{
		printf("nbytes (%d) == 0 and save[%d] (%s) is NULL... Return (0)\n", nbytes, fd, save[fd]);
		return (0);
	}
	else
	{
		printf("\033[1;33m");
		printf("\nSend to gnl_new_line!\n");
		printf("\033[0m");
		printf("\n");
		return (gnl_new_line(&save[fd], line));
	}
		
}
/*
** The get_next_line function reads a file and returns the line ending with a
** newline character from a file descriptor. A static variable is used, so that
** whenever get_next_line is called, it remembers the previous function call.
** When get_next_line is first called, we check to see if our static variable
** **save is empty. If it is, we allocate memory for it using our buff string.
** In the loop, we will continue to read more of the line and join them together
** using a temporary string. This temporary string will replace the stored data
** each iteration so that we can keep track of how much is read and delete
** the previous stored data. This is needed because we are only reading so many
** n-bytes at a time decided by our BUFF_SIZE. If we read at each iteration
** without freeing memory, then we would have memory leaks. The loop breaks when
** a newline is encountered. Finally, we call output function to check what
** should be returned.
*/

int		get_next_line(int fd, char **line)
{
	static char		*save[255];
	char			buffer[BUFFER_SIZE];
	char			*tmp;
	int				nbytes;
	
	while ((nbytes = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[nbytes] = '\0';
		printf("\033[1;32m");
		printf("\nNew loop!\n");
		printf("\033[0m");
		printf("\n\t\tbuffer[%d]\n", nbytes);
		printf("-------------------------------------------\n");
		printf("[%s]\n", buffer);
		printf("-------------------------------------------\n");
		printf("\n");
		if (save[fd] == NULL)
		{
			printf("\nStatic var is empty... Dup buffer to static var:");
			save[fd] = ft_strdup(buffer);
			printf("\n\t\tsave[%d]\n", fd);
			printf("-------------------------------------------\n");
			printf("[%s]\n", save[fd]);
			printf("-------------------------------------------\n");
			printf("\n");
		}
		else
		{
			printf("\nStatic var is not empty... Join save[%d] and buffer to tmp:", fd);
			tmp = ft_strjoin(save[fd], buffer);
			printf("\n\t\ttmp\n");
			printf("-------------------------------------------\n");
			printf("[%s]\n", tmp);
			printf("-------------------------------------------\n");
			printf("\n");	
			free(save[fd]);
			printf("\nFree save[%d]", fd);
			printf("\n\t\tsave[%d]\n", fd);
			printf("-------------------------------------------\n");
			printf("[%s]\n", save[fd]);
			printf("-------------------------------------------\n");
			printf("\n");
			save[fd] = tmp;
			printf("\nAppend tmp to save[%d]", fd);
			printf("\n\t\tsave[%d]\n", fd);
			printf("-------------------------------------------\n");
			printf("[%s]\n", save[fd]);
			printf("-------------------------------------------\n");
			printf("\n");
		}
		printf("\nSearching save[%d] for NL", fd);
		printf("\n\t\tsave[%d]\n", fd);
		printf("-------------------------------------------\n");
		printf("[%s]\n", save[fd]);
		printf("-------------------------------------------\n");
		printf("\n");
		if (ft_strchr(save[fd], '\n'))
		{
			printf("\033[1;33m");
			printf("\nFound NL in save[%d]... Broke the loop!\n", fd);
			printf("\033[0m");
			break ;		
		}
		printf("\033[1;33m");
		printf("No NL in save[%d]... Loop!\n", fd);
		printf("\033[0m");
	}
	printf("\033[1;33m");
	printf("\nGo to gnl_check_ret!\n");
	printf("\033[0m");
	printf("\n");
	return (gnl_check_ret(save, line, nbytes, fd));
}