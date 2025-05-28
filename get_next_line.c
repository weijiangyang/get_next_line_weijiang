/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:11:06 by weiyang           #+#    #+#             */
/*   Updated: 2025/05/28 17:19:20 by weiyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_stash(int fd, char *stash, char *buffer)
{
	// pour read et reserve dans buf
	ssize_t		bytes_read;
	char		*tmp;

	bytes_read = 1;
	// le boucle se repeate quand bytes_read > 0 et le reserve est NULL ou le reserve ne contient pas \n
	while (bytes_read > 0 && (!stash || !end_line(stash)))
	{
		// read dans le buffer
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		// si read est echoue, liberer stash , et retourne NULL
		if (bytes_read < 0)
		{
			free (stash);
			return (NULL);
		}
		if (bytes_read > 0)
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
	// extraire la ligne pour afficher et update le reserve : stash
	char	*tmp;
	char	*line;
	char	*next;
	// extraire la ligne jusqu'qu '\n' , ajouter '\0' a la fin
	line = extract_line(*stash);
	// su extrait est echoue, liberer le stash et retourne NULL
	if (!line)
	{
		free (*stash);
		*stash = NULL;
		return (NULL);
	}
	// tem, c'est pour gerer le memoire intermediaire pendant la concatenation
	tmp = *stash;
	// enlever la partie ligne de stash pour update le stash
	next = tmp + ft_strlen(line);
	// si seulement \0 est reste, le stash est NULL
	if (*next == '\0')
		*stash = NULL;
	// sino le stash est update en next
	else
		*stash = ft_strdup(next);
	// liberer tmp
	free (tmp);
	// retourne line
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;
	char		*buffer;

	// si open est echoue ou buffer n'existe pas
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// allocation buffer
	buffer = (char *)malloc (BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	// read and reserve dans stash, stash concatener avec bytes_read
	stash = read_and_stash(fd, stash, buffer);
	// liberer buffer
	free (buffer);
	// si stash est NULL ou vide, retourne NULL
	if (!stash || stash[0] == '\0')
	{
		// free et liberer stash
		if (stash)
			free (stash);
		stash = NULL;
		return (NULL);
	}
	// extraire ligne a afficher et update le stash
	line = extract_and_update (&stash);
	return (line);
}
