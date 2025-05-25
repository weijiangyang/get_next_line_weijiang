/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:11:06 by weiyang           #+#    #+#             */
/*   Updated: 2025/05/25 17:37:18 by weiyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_stash(int fd, char *stash, char *buffer)
{
	ssize_t		bytes_read;
	char		*tmp;

	bytes_read = 1;
	while (bytes_read > 0 && (!stash || !end_line(stash)))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (!stash)
			stash = ft_strdup(buffer);
		else
		{
			tmp = stash;
			stash = ft_strjoin(stash, buffer);
			free (tmp);
		}
	}
	return (stash);
}

char	*extract_and_update(char **stash)
{
	char	*tmp;
	char	*line;
	char	*next;

	line = extract_line(*stash);
	if (!line)
	{
		free (*stash);
		*stash = NULL;
		return (NULL);
	}
	tmp = *stash;
	next = tmp + ft_strlen(line);
	if (*next == '\0')
		*stash = NULL;
	else
		*stash = ft_strdup(next);
	free (tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc (BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	stash = read_and_stash(fd, stash, buffer);
	free (buffer);
	if (!stash || stash[0] == '\0')
	{
		if (stash)
			free (stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_and_update (&stash);
	return (line);
}
