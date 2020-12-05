/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/16 09:47:53 by abeznik       #+#    #+#                 */
/*   Updated: 2020/12/05 12:46:10 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	int len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*ft_strdup(char *s1)
{
	int		i;
	int		size;
	char	*str;

	i = 0;
	size = 0;
	while (s1[size])
		size += 1;
	str = (char*)malloc(sizeof(*str) * size + 1);
	if (str == NULL)
		return (NULL);
	while (i < size)
	{
		str[i] = s1[i];
		i++;
	}
	str[size] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup(s2));
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len && s[i + start] != '\0')
	{
		res[i] = s[i + start];
		i++;
	}
	res[i] = '\0';
	return (res);
}
