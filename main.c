/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:41:16 by weiyang           #+#    #+#             */
/*   Updated: 2025/05/25 14:46:34 by weiyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int fd = open("one_line.txt", O_RDONLY);
	char *line;

	// Appel 1 : lit "Hello\n"
	line = get_next_line(fd); 
	printf("line1 = %s", line); // => "Hello\n"
	free(line);

	// Appel 2 : EOF -> doit retourner NULL proprement
	line = get_next_line(fd); 
	printf("line2 = %s", line); // => NULL

}


