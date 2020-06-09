//
// Created by cxim1 on 08.06.2020.
//
#include <stdio.h>
#include "libft/libft.h"

int main(int i, char**str)
{
	int fd;
	char **lin;
	//printf("%s\n", str[1]);
	fd = open(str[1], O_RDONLY);
	i = get_next_line(fd, lin);
	int j =0;
	while (lin[j] != NULL)
	{
		printf("%s", lin[j]);
		j++;
	}
}