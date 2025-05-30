
#include <fcntl.h>	// open
#include <unistd.h> // close
#include <stdio.h>	// printf, perror
#include <stdlib.h> // malloc, free

char *get_next_line(int fd);
int main(int argc, char **argv)
{
    int fd;
    char *line;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return (1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }
    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
	line = get_next_line(fd);
    }
    close(fd);
    return (0);
}

