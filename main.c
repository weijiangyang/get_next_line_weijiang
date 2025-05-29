/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:09:31 by weiyang           #+#    #+#             */
/*   Updated: 2025/05/29 21:28:26 by weijiangyang     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>      // open
#include <unistd.h>     // close
#include <stdio.h>      // printf, perror
#include <stdlib.h>     // malloc, free

// Prototypage de get_next_line
char *get_next_line(int fd);

int main(int argc, char **argv)
{
	int fd;
	char *line;

	fd = 0;
	if (argc ==2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			perror("Error opening file");
			return 1;
		}
		line = get_next_line(fd);
		while (line)
		{
			printf ("%s", line);
			free (line);
			line = get_next_line(fd);
			if (!line)
				return (0);
		}
		close (fd);
	}
	while ((line = get_next_line(0)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	return 0;
}

