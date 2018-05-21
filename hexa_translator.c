#include <fcntl.h>
#include "corewar.h"
#include <stdio.h>
#define PATH "/Users/dwald/corewar/hexa_file"


int		main(int ac, char **av)
{
	int fd;
	int fd_file;
	int ret;
	char *line;
	int		c;

	c = '#';	
	line = NULL;
	if ((fd = open(av[1], O_RDONLY)) == -1)
	{
		printf("open failed\n");
		return (-1);
	}
	if ((fd_file = open(PATH, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU | S_IRGRP | S_IROTH)) == -1)
	{
		printf("open hexa_file failed\n");
		return (-1);
	}
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		for (int i = 0; line[i] != '\0';)
		{
			c = line[i++];
			dprintf(fd_file, "%o", c);
		}
		dprintf(fd_file, "\n");
		free(line);
	}	
	if (close(fd) == -1)
	{
		printf("close failed\n");
		return (-1);
	}
	if (close(fd_file) == -1)
	{
		printf("close failed\n");
		return (-1);
	}
	return (0);
}
