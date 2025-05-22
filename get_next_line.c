/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:11:06 by weiyang           #+#    #+#             */
/*   Updated: 2025/05/22 11:57:38 by weiyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//extrait_line : pour extrait les characteres avant \n ou \0

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define	BUFFER_SIZE 1024

char *extract_line(char *str)
{
	int	i;
	char*	extract;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	extract = (char *) malloc ((i + 2) * sizeof (char));
	if (!extract)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		extract[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		extract[i] = '\n';
		i++;
	}
	extract[i]= '\0';
	return (extract);
}

int     ft_strlen(char *str)
{
	int     size;

	size = 0;
	while (*str)
	{
		size++;
		str++;
	}
	return (size);
}
	 	

char	*ft_strjoin(char  *s1, char  *s2)
{
	char	*ptr;
	char	*dst;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	ptr = malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	dst = ptr;
	while (*s1)
	{
		*dst = *s1;
		dst++;
		s1++;
	}
	while (*s2)
	{
		*dst = *s2;
		dst++;
		s2++;
	}
	*dst = '\0';
	return (ptr);
}

char	*ft_strdup(char *s)
{
	char	*ptr;
	char	*dst;

	ptr = malloc ((ft_strlen(s) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	dst = ptr;
	while (*s)
		*dst++ = *s++;
	*dst = '\0';
	return (ptr);
}

int	end_line(char *str, int	size)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while ((str[i] != '\n' || str[i] != '\0') && i < size - 1)
		i++;
	if (str[i] == '\n' || str[i] == '\0')
		return (1);
	return (0);
}
	

char *get_next_line(int fd)
{
    static char *stash = NULL;
    char        *buffer;
    char        *line;
    char        *tmp;
    ssize_t     bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return NULL;

    bytes_read = 1;
    while (bytes_read > 0 && (!stash || !end_line(stash, BUFFER_SIZE)))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(buffer);
            return NULL;
        }
        buffer[bytes_read] = '\0';
	// mettre buffer dans stash
	if (!stash)
	{
	    stash = ft_strdup(buffer);
	    //liberer buffer
	    free (buffer);
	}
	// mettre la union entre stash et buffer 
	else
	{
    		tmp = stash;
    		stash = ft_strjoin(stash, buffer);
		// liberer stash
   		free(tmp);
		// liberer buffer
		free (buffer);
	}

    }

    if (!stash || stash[0] == '\0')
    {
	free (stash);
	return NULL;
     }

    line = extract_line(stash);
    tmp = stash;
    stash = ft_strdup(stash + ft_strlen(line)); // remove extracted line from stash
    free (tmp);
    return line;
}

int main(void)
{
    int     fd;
    char    *line;
    char    *line2;
    char	*result;
    int		end;
    fd = open("text.txt", O_RDONLY);
    if (fd == -1)
        return 1;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
   /* line = "hello world!\nwelcome to this club!";
    line2 = "ok, this is ok";
    end = end_line(line, 100);
    result = ft_strdup(line2);
    printf("%d", end);*/

    return 0;
}
	
