//
// Created by И Б on 03.05.20.
//
#include "ft_ls.h"

int 	check_p(char *str)
{
	int 	res;
	int 	i;
	char	*tmp;

	tmp = str;
	res = 0;
	i = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == 'F')
			res = 1;
		if (tmp[i] =='p')
			res = 2;
		i++;
	}
	return (res);
}

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
		else if (str[i] == 'u')
			inc->u = 1;
		else if (str[i] == '1')
			inc->one = 1;
		else if (str[i] == 'c')
			inc->c = 1;
		else if (str[i] == 'S')
			inc->s_big = 1;
		else if (str[i] == 'U')
			inc->u_big = 1;
		else if (str[i] == 'F')
			inc->f_big = 1;
		else if (str[i] == 'p')
			inc->p = check_p(str);
		else if (str[i] == 'd')
			inc->d = 1;
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
			//free(tmp->some);
//			if (tmp->dir)
			free(tmp->dir);
//			if (tmp->full_path)
			free(tmp->full_path);
			free(tmp);
		}
	}
	if (inc->path)
		free(inc->path);
	free(inc->dump_dir);
//	if (inc->dump_dir_tmp)
	free(inc->dump_dir_tmp);
//	if (inc->dirp && inc->rr == 0)
	closedir(inc->dirp);
	free(inc);
	inc = NULL;
}

int 	dir_file(t_inc *inc)
{
	lstat(inc->lst->dir, &inc->sb);
	if (inc->sb.st_mtim.tv_sec != 0)
	{
		if (S_ISLNK(inc->sb.st_mode) && (inc->l == 0 && inc->f_big == 0)) //for simb link
			return 1;
		else if (S_ISDIR(inc->sb.st_mode))
			return 1;
		else
			return 0;
	}
	return -1;
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
	while (i < argc)
	{
		if (argv[i][0] != '-')
		{
			tmp = (t_dir *)ft_memalloc(sizeof(t_dir));
			//str_tmp = argv[i];
			tmp->dir = ft_strdup(argv[i]);
			tmp->next = inc->lst;
			//inc->dump_dir = ft_strdup(str_tmp);
			inc->lst = tmp;
		}
		else if (add_args(inc, argv[i]) == 0)
			return (0);
		i++;
	}
	if (inc->lst == NULL)
		make_lst(inc);
	i = dir_file(inc);
	//ft_printf("%d\n", i);
	if (i >= 0)
		ft_ls(inc, i);
	else
	{
		ft_putstr("/bin/ls: "); //потом исправить как фт_лс
		ft_putstr("cannot access '");
		ft_putstr(inc->lst->dir);
		ft_putendl("': No such file or directory");
//		free(inc->dump_dir_tmp);
		free_l(inc);
		return (-1);
	}
	//free(str_tmp);
//	free_lst(tmp);
	//free(tmp->dir);
	free_l(inc);
//	free(str_tmp);
	return (0);
}
//==2135==    definitely lost: 763 bytes in 91 blocks
//==2135==    indirectly lost: 33,562 bytes in 30 blocks
