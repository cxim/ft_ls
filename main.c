//
// Created by И Б on 03.05.20.
//
#include "ft_ls.h"

int		add_args(t_inc *inc, char *str)
{
	int 	i;
	char 	*tmp;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == 'l')
			inc->l = 1;
		else if (str[i] == 'r')
			inc->r = 1;
		else if (str[i] == 't')
			inc->t = 1;
		else if (str[i] == 'a')
			inc->a = 1;
		else if (str[i] == 'R')
			inc->rr = 1;
		else
		{
			tmp = ft_strjoin(str, ": Invalid argument\n");
			ft_putstr_fd(tmp, 2);
			free_l(inc);
			free(tmp);
			exit (2);
		}
		i++;
	}
	return (1);
}

void	make_lst(t_inc *inc)
{
	inc->lst = (t_dir*)malloc(sizeof(t_dir));
	inc->lst->dir = ft_strdup(".");
	inc->lst->full_path = ft_strnew(0);
	inc->lst->next = NULL;
}

void	free_lst(t_dir *dir)
{
	t_dir *tmp;
	if (dir)
	{
		while (dir != NULL)
		{
			tmp = dir;
//			if (dir->dir)
			dir = dir->next;
			free(tmp->dir);
//			if (dir->full_path)
			free(tmp->full_path);
			//free(dir);

			free(tmp);
		}
	}
	//free(dir);
	dir = NULL;
}

void	free_l(t_inc *inc)
{
	t_dir *tmp;
	if (inc->lst)
	{
		while (inc->lst != NULL)
		{
			tmp = inc->lst;

			inc->lst = inc->lst->next;
//			if (tmp->dir)
			free(tmp->dir);
//			if (tmp->full_path)
			free(tmp->full_path);
			free(tmp);
		}
	}
	if (inc->path)
		free(inc->path);
//	if (inc->dirp && inc->rr == 0)
	closedir(inc->dirp);
	free(inc);
	inc = NULL;
}

int main(int argc, char **argv)
{
	int 	i;
	t_inc	*inc;
	t_dir	*tmp;
	char 	*str_tmp;

	i = 1;
	str_tmp = NULL;
	inc = (t_inc *)ft_memalloc(sizeof(t_inc));
	tmp = inc->lst;
	while (i < argc)
	{
		if (argv[i][0] != '-')
		{
			//ft_printf("lol\n");
			tmp =(t_dir *)ft_memalloc(sizeof(t_dir));
			str_tmp = argv[i];
			tmp->dir = ft_strdup(str_tmp);
			tmp->next = inc->lst;
			inc->lst = tmp;
		}
		else if (add_args(inc, argv[i]) == 0)
			return (0);
		i++;
	}
	if (inc->lst == NULL)
		make_lst(inc);
	ft_ls(inc, str_tmp);
	//free(str_tmp);
//	free_lst(tmp);
	//free(tmp->dir);
	free_l(inc);
	return (0);
}
//==2135==    definitely lost: 763 bytes in 91 blocks
//==2135==    indirectly lost: 33,562 bytes in 30 blocks
