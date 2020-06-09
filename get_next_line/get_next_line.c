#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

char *give_remainder(char **line, char *remainder)
{
	char *p_n;
	char *tmp;

	if ((p_n = ft_strchr(remainder, '\n')))
	{
		*p_n = '\0';
		tmp = *line;
		if (!(*line = ft_strjoin(*line, remainder)))
			return (NULL);
		free(tmp);
		*p_n = '\n';
	}
	else
	{
		tmp = *line;
		if (!(*line = ft_strjoin(*line, remainder)))
			return (NULL);
		free(tmp);
	}
	return (*line);
}

char *remake_remainder(char *remainder)
{
	char *p_n;
	char *tmp;

	if ((p_n = ft_strchr(remainder, '\n')))
	{
		tmp = remainder;
		remainder = ft_strdup(++p_n);
		free(tmp);
	}
	else
	{
		tmp = remainder;
		remainder = ft_strdup("");
		free(tmp);
	}
	return (remainder);
}

void	rem(char ***line, char **remainder, char **p_n)
{
	*p_n = ft_strchr(*remainder, '\n');
	**line = give_remainder(*line, *remainder);
	*remainder = remake_remainder(*remainder);
}

void	rem2(char **p_n, char**tmp, char **remainder)
{
	**p_n = '\0';
	*tmp = *remainder;
	*remainder = ft_strdup(++(*p_n));//защитить
	free(*tmp);
}

int     get_next_line(int fd, char **line) {
	static char *remainder;
	char buf[BUFFER_SIZE + 1];
	int readed;
	char *p_n;
	char *tmp;

	p_n = NULL;
	if (!line || fd < 0 || BUFFER_SIZE < 1 || !(*line = malloc(BUFFER_SIZE + 1)))
		return (-1);
	*line[0] = '\0';
	if (remainder)
		rem(&line, &remainder, &p_n);
	while (!p_n && (readed = read(fd, buf, BUFFER_SIZE)) > 0) {
		buf[readed] = '\0';
		if ((p_n = ft_strchr(buf, '\n')))
			rem2(&p_n, &tmp, &remainder);
		tmp = *line;
		*line = ft_strjoin(*line, buf);//защитить
		free(tmp);
	}
	if (readed < 0)
		return (-1);
	if (!remainder)
		return 0;
	return (readed || ft_strlen(remainder)) ? 1 : 0;
}

