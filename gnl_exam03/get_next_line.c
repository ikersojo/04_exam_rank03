/*
Assignment name : get_next_line
Expected files : get_next_line.c get_next_line.h
Allowed functions: read, free, malloc

Write a function named get_next_line which prototype should be:
char *get_next_line(int fd);

Your function must return a line that has been read from the file descriptor passed as parameter.
What we call a "line that has been read" is a succesion of 0 to n characters that end with '\n'
(ascii code 0x0a) or with End Of File (EOF). The line should be returned including the '\n' in case
there is one at the end of the line that has been read. When you've reached the EOF, you must store
the current buffer in a char * and return it.
If the buffer is empty you must return NULL.
In case of error return NULL.
In case of not returning NULL, the pointer should be free-able.
Your program will be compiled with the flag -D BUFFER_SIZE=xx, which has to be used as the buffer size
for the read calls in your functions. Your function must be memory leak free. When you've reached the EOF,
your function should keep 0 memory allocated with malloc, except the line that has been returned.
Caling your function get_next_line in a loop will therefore allow you to read the text avaiable on
a file descriptor one line at a time until the end of the text, no matter the size of either the text or one of its lines.
Make sure that your function behaves well when it reads from a file, from the standard output, from a redirection, etc...
No call to another function will be done on the file descriptor between 2 calls of get_next_line.
Finally we consider that get_next_line has an undefined behaviour when reading from a binary file.
*/

#include "get_next_line.h"

#define FD_LIMIT 1024

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#if (BUFFER_SIZE > 1000000)
# undef BUFFER_SIZE
# define BUFFER_SIZE 1000000
#endif

int	ft_strlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (*str++)
		len++;
	return (len);
}

int	ft_isline(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

int	ft_get_line_len(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i++) == '\n')
			return (i);
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (join == NULL)
		return (NULL);
	i = 0;
	while (*(s1 + i))
	{
		*(join + i) = *(s1 + i);
		i++;
	}
	j = 0;
	while (*(s2 + j))
		*(join + i++) = *(s2 + j++);
	*(join + i) = '\0';
	return (join);
}

static void	ft_read_buffer(int fd, char **holder)
{
	char	*buff;
	char	*join;
	int		bytes;

	while (1)
	{
		if (ft_isline(*holder) == 1)
			break ;
		buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buff == NULL)
		{
			*holder = NULL;
			return ;
		}
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes <= 0)
		{
			free(buff);
			return ;
		}
		*(buff + bytes) = '\0';
		if (*holder == NULL)
			*holder = buff;
		else
		{
			join = ft_strjoin(*holder, buff);
			free (buff);
			free (holder);
			*holder = join;
		}
	}
}

char	*ft_extract_line(char **holder)
{
	char	*line;
	char	*remainder;
	int		len;
	int		i;
	int		j;

	len = ft_get_line_len(*holder);
	if (len == 0)
		return (NULL);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		*(line + i) = *(*holder + i);
		i++;
	}
	*(line + i) = '\0';
	remainder = (char *)malloc(sizeof(char) * (ft_strlen(*holder) + 1));
	if (remainder == NULL)
		return (NULL);
	j= 0;
	while (*(*holder + i))
	{
		*(remainder + j) =  *(*holder + i);
		j++;
		i++;
	}
	*(remainder + j) = '\0';
	free (*holder);
	*holder = remainder;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*holder;
	char		*line;

	if (fd == -1 || fd > FD_LIMIT || BUFFER_SIZE < 1)
		return (NULL);
	ft_read_buffer(fd, &holder);
	if (holder == NULL || *holder =='\0')
		return (NULL);
	line = ft_extract_line(&holder);
	if (line == NULL)
		free(holder);
	return (line);
}
