#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*get_next_line(int fd);

int	main(void)
{
	char	*line;
	int		fd;
	int		i;

	fd = open("prueba.txt", O_RDONLY);
	printf("fd = %d\n", fd);

	i = 0;
	while (i < 10)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (line != NULL)
			free (line);
		i++;
	}
	close(fd);
	return (0);
}