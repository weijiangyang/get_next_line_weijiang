/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:11:06 by weiyang           #+#    #+#             */
/*   Updated: 2025/05/27 17:03:18 by weiyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		if (!stash || stash[0] == '\0')
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

char	*extract_and_update(t_fd_buffer *current, char **stash)
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
	current -> stash = *stash;
	return (line);
}

t_fd_buffer	*get_fd_node(t_fd_buffer **fd_list, int fd)
{
	t_fd_buffer	*current;
	t_fd_buffer	*new_node;

	if (fd < 0 || fd >= 1024)
	{
		close (fd);
		return (NULL);
	}
	current = *fd_list;
	while (current)
	{
		if (current -> fd == fd)
			return (current);
		current = current -> next;
	}
	new_node = (t_fd_buffer *)malloc (sizeof (t_fd_buffer));
	new_node -> fd = fd;
	new_node -> stash = NULL;
	new_node -> next = *fd_list;
	*fd_list = new_node;
	return (new_node);
}

void	free_fd_node(t_fd_buffer **fd_list, int fd)
{
	t_fd_buffer	*cur;
	t_fd_buffer	*prev;

	cur = *fd_list;
	prev = NULL;
	while (cur)
	{
		if (cur->fd == fd)
		{
			if (prev)
				prev->next = cur->next;
			else
				*fd_list = cur->next;
			free(cur->stash);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

char	*get_next_line(int fd)
{
	char					*line;
	char					*buffer;
	char					*stash;
	static t_fd_buffer		*fd_list;
	t_fd_buffer				*current_node;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	current_node = get_fd_node (&fd_list, fd);
	buffer = (char *)malloc (BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	stash = read_and_stash(fd, current_node -> stash, buffer);
	free (buffer);
	current_node -> stash = stash;
	if (!current_node -> stash || *current_node -> stash == '\0' )
	{
		free_fd_node(&fd_list, fd);
		return (NULL);
	}
	line = extract_and_update (current_node, &stash);
	return (line);
}
