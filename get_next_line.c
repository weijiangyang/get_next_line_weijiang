/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:11:06 by weiyang           #+#    #+#             */
/*   Updated: 2025/05/24 15:48:52 by weiyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_utils.c"

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
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		tmp = stash;
		if (!stash)
			stash = ft_strdup(buffer);
		else
			stash = ft_strjoin(stash, buffer);
		free (tmp);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;
	char		*tmp;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc (BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	stash = read_and_stash(fd, stash, buffer);
	if (!stash || stash[0] == '\0')
	{
		free (stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash);
	tmp = stash;
	stash = ft_strdup(stash + ft_strlen(line));
	free (tmp);
	return (line);
}

int     main(void)
{
        int             fd;
        char    *line;

        fd = open ("text.txt", O_RDONLY);
        if (fd == -1) 
                return (1);
        line = get_next_line(fd);
        while (line != NULL)
        {
                printf("%s", line);
                free(line);
                line = get_next_line(fd);
        }
        close(fd);
        return (0);
}

