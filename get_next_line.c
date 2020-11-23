/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/16 09:47:36 by abeznik       #+#    #+#                 */
/*   Updated: 2020/11/23 16:37:54 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static char		*ft_strchr(const char *s, int c)
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

static char		*ft_strnew(size_t size)
{
	char	*s;
	size_t	i;

	i = 0;
	s = (char*)malloc(size + 1);
	if (s == NULL)
		return (NULL);
	while (i < size)
	{
		s[i] = '\0';
		i++;
	}
	s[size] = '\0';
	return (s);
}

static void		ft_strdel(char **as)
{
	if (as)
	{
		free(*as);
		*as = NULL;
	}
	return ;
}

static int		ft_new_line(char **stack, char **line, int fd, int ret_read)
{
	int				len;
	char			*tmp_stack;

	len = 0;
	while (stack[fd][len] != '\n' && stack[fd][len] != '\0')
		len++;
	if (stack[fd][len] == '\n')
	{
		*line = ft_substr(stack[fd], 0, len);
		tmp_stack = ft_strdup(stack[fd] + len + 1);
		free(stack[fd]);
		stack[fd] = tmp_stack;
		if (stack[fd][0] == '\0')
			ft_strdel(&stack[fd]);
	}
	else if (stack[fd][len] == '\0')
	{
		if (ret_read == BUFFER_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(stack[fd]);
		ft_strdel(&stack[fd]);
	}
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static char		*stack[255];
	char			heap[BUFFER_SIZE + 1];
	char			*tmp_stack;
	int				ret_read;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((ret_read = read(fd, heap, BUFFER_SIZE)) > 0)
	{
		heap[ret_read] = '\0';
		if (stack[fd] == NULL)
			stack[fd] = ft_strnew(1);
		tmp_stack = ft_strjoin(stack[fd], heap);
		free(stack[fd]);
		stack[fd] = tmp_stack;
		if (ft_strchr(heap, '\n'))
			break ;
	}
	if (ret_read < 0)
		return (-1);
	else if (ret_read == 0 && (stack[fd] == NULL || stack[fd][0] == '\0'))
		return (0);
	return (ft_new_line(stack, line, fd, ret_read));
}
