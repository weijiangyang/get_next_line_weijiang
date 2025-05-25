
#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
	int	i;

	i = 1;
	int fd = open("fichier.txt", O_RDONLY);
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
    		printf("line %d: [%s]", i, line);
		i++;

		free(line);
	}
	close(fd);
	return (0);
}

