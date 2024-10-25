/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:06:48 by witong            #+#    #+#             */
/*   Updated: 2024/10/02 09:22:25 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"
#include "../../inc/libft.h"

static char	*extract_line(char **cache)
{
	char	*line;
	char	*tmp;
	size_t	i;

	i = 0;
	while ((*cache)[i] && (*cache)[i] != '\n')
		i++;
	line = ft_substr(*cache, 0, i + 1);
	if (!line)
	{
		free(*cache);
		*cache = NULL;
		return (NULL);
	}
	if ((*cache)[i] == '\n')
		tmp = ft_strdup(*cache + i + 1);
	else
		tmp = NULL;
	free(*cache);
	*cache = tmp;
	return (line);
}

static char	*read_and_cache(char **cache, int fd)
{
	char	*buffer;
	char	*tmp;
	ssize_t	read_size;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	read_size = read(fd, buffer, BUFFER_SIZE);
	while (read_size > 0)
	{
		buffer[read_size] = '\0';
		tmp = ft_strjoin(*cache, buffer);
		free(*cache);
		*cache = tmp;
		if (ft_strchr(buffer, '\n'))
			break ;
		read_size = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (read_size < 0 || !*cache || !**cache)
	{
		free(*cache);
		*cache = NULL;
		return (NULL);
	}
	return (extract_line(cache));
}

char	*get_next_line(int fd)
{
	static char	*cache[MAX_FD];

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (!cache[fd])
		cache[fd] = ft_strdup("");
	if (!cache[fd])
		return (NULL);
	return (read_and_cache(&cache[fd], fd));
}
