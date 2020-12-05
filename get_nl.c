/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_nl.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/05 11:46:41 by abeznik       #+#    #+#                 */
/*   Updated: 2020/12/05 14:14:44 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void			ft_strdel(char **as)
{
	if (as)
	{
		free(*as);
		*as = NULL;
	}
	return ;
}

static char			*ft_strchr(const char *s, int c)
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

static int			gnl_new_line(char **save, char **line, int fd)
{
	size_t			len;
	char			*tmp;

	len = 0;
	while (save[fd][len] != '\n' && save[fd][len] != '\0')
		len++;
	if (save[fd][len] == '\n')
	{
		*line = ft_substr(save[fd], 0, len);
		tmp = ft_strdup(save[fd] + len + 1);
		free(save[fd]);
		save[fd] = tmp;
		if (save[fd][0] == '\0')
			ft_strdel(&(save[fd]));
	}
	else if (save[fd][len] == '\0')
	{
		*line = ft_strdup(save[fd]);
		ft_strdel(&(save[fd]));
	}
	return (1);
}

static int			gnl_check_ret(char **save, char **line, int nbytes, int fd)
{
	if (nbytes < 0)
		return (-1);
	else if (nbytes == 0 && save[fd] == NULL)
		return (0);
	else
		return (gnl_new_line(save, line, fd));
}

int					get_next_line(int fd, char **line)
{
	static char		*save[255];
	char			buffer[BUFFER_SIZE];
	char			*tmp;
	int				nbytes;

	while ((nbytes = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[nbytes] = '\0';
		if (save[fd] == NULL)
			save[fd] = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(save[fd], buffer);
			free(save[fd]);
			save[fd] = tmp;
		}
		if (ft_strchr(save[fd], '\n'))
			break ;
	}
	return (gnl_check_ret(save, line, nbytes, fd));
}
