/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:09:31 by weiyang           #+#    #+#             */
/*   Updated: 2025/05/29 11:11:13 by weiyang          ###   ########.fr       */
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
	char *line;
	int	fd_list[argc - 1];
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	if (argc >=2)
	{
		while (i < argc - 1)
		{
			fd_list[i] = open (argv[i + 1], O_RDONLY);
			i++;
		}
		while (count < argc - 1) 
		{
			i = 0;
			while (i < argc - 1)
			{
				line = get_next_line (fd_list[i]);
				if (line != NULL)
					printf ("%s", line);
				else	
				{
					close (fd_list[i]);
					fd_list[i] = -1;
					count ++;
				}
				free (line);
				i++;
			}	
		}
	}
	while ((line = get_next_line(0)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	return 0;
}

