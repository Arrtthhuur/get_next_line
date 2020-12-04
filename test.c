/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/16 11:16:37 by abeznik       #+#    #+#                 */
/*   Updated: 2020/11/30 17:50:13 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*ptr_dst;
	char	*ptr_src;
	size_t	i;

	ptr_dst = (char *)dst;
	ptr_src = (char *)src;
	i = 0;
	if (ptr_dst < ptr_src)
	{
		while (i < len)
		{
			*(ptr_dst + i) = *(ptr_src + i);
			i++;
		}
	}
	else
	{
		while (len > 0)
		{
			*(ptr_dst + (len - 1)) = *(ptr_src + (len - 1));
			len--;
		}
	}
	return (dst);
}

size_t		ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char		*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen((char *)s1);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_memmove(ptr, s1, len);
	*(ptr + len) = '\0';
	return (ptr);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	ptr = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_memmove(ptr, s1, len_s1);
	ft_memmove(ptr + len_s1, s2, len_s2);
	ptr[len_s1 + len_s2] = '\0';
	return (ptr);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	if (!s)
		return (NULL);
	if (start + 1 > ft_strlen(s) || !len)
		return (ft_strdup(""));
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (len > i && s[start + i])
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}


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

int			main(void)
{
	char	*line;
	int		fd;
	int		line_nb;

	fd = open("test2.txt", O_RDONLY);
	line_nb = 1;
	while (get_next_line(fd, &line) == 1)
	{
		printf("Line #%d:	%s\n", line_nb, line);
		line_nb++;
	}
	return (0);
}
