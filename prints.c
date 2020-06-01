//
// Created by И Б on 04.05.20.
//

#include "ft_ls.h"

//int		compare_time(t_dir d1, t_dir d2)
//{
//}
void	big_r(t_dir *lst, t_inc *inc)
{
	t_dir	*tmp;

	tmp = lst;

	while (tmp != NULL)
	{

		if (tmp->true_dir == 100 && tmp->dir[0] != '.')
		{
			//if (tmp->true_dir == 1)
			closedir(inc->dirp);
			do_operation(tmp->full_path, inc);
		}
		tmp = tmp->next;

	}

}
void	get_time(struct stat fstat, t_dir *tmp)
{
	char 	buff[13];
	char 	*str;
	char 	buf[64];
	size_t 	len;

	(void)fstat;
	str = ctime(&tmp->time);
	ft_memcpy(buff, &str[4], 12);
	buff[12] = '\0';
	ft_putstr(buff);
	ft_putstr(" ");
	ft_putstr(tmp->dir);
	if (S_ISLNK(fstat.st_mode))
	{
		ft_putstr(" -> ");
		len = readlink(tmp->full_path, buf, 64);
		buf[len] = '\0';
		ft_putstr(buf);
	}
}

void 	get_user(struct stat fstat)
{
//	char 			*str;
	struct passwd	*pw;
	struct group	*gp;
	char 			*name;
	char 			*name_g;

	pw = getpwuid(fstat.st_uid);
	gp = getgrgid(fstat.st_gid);
	name = pw->pw_name;
	name_g = gp->gr_name;
//	str = ft_strjoin(name, "  ");
//	str = ft_strjoin(str , name_g);
//	str = ft_strjoin(str, " ");
//	ft_putstr(str);
	ft_printf("%s%s%s", name, "  ", name_g, " ");
//	free(str);
//	free(name);
//	free(name_g);
	//free(pw->pw_name);
	//free(gp);
}

void	get_permission(t_dir *tmp, struct stat fstat)
{
	if (tmp->true_dir)
		ft_putchar('d');
	else
		ft_putchar((S_ISLNK(fstat.st_mode)) ? '1' : '-');
	ft_putchar((fstat.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((fstat.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((fstat.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((fstat.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((fstat.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((fstat.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((fstat.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((fstat.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((fstat.st_mode & S_IXOTH) ? 'x' : '-');
	ft_putstr("  ");
}
void 	print_blocks(t_dir *dir)
{
	struct stat		fstat;
	int				res;
	t_dir			*tmp;
	int				get_int;

	res = 0;
	tmp = dir;
	while (tmp != NULL)
	{
		lstat(tmp->full_path, &fstat);
		get_int = fstat.st_blocks;
		res = res + get_int;
		tmp = tmp->next;
	}
	ft_putstr("total ");
	ft_putnbr(res / 2);
	ft_putchar('\n');
}

int		num_len(int num)
{
	int		count;

	count = 1;
	if (num < 10 && num > -10)
		return (count);
	while (num > 10 || num < -10)
	{
		num =num / 10;
		count++;
	}
	return (count);
}

void	print_l(t_dir *lst)
{
	t_dir			*tmp;
	struct stat		fstat;
	//char 			*bytes;
	int 			len;
	int 			i;
	int				some;

	tmp = lst;
	print_blocks(tmp);
	while (tmp != NULL)
	{
		lstat(tmp->full_path, &fstat);
		get_permission(tmp, fstat);
		if (fstat.st_nlink > 9)
			ft_putnbr(fstat.st_nlink);
		else
		{
			ft_putstr(" ");
			ft_putnbr(fstat.st_nlink);
		}
		ft_putstr(" ");
		get_user(fstat);
		ft_putstr(" ");
		i = 5;
		//bytes = ft_itoa(fstat.st_size);
		some = num_len(fstat.st_size);
		//len = ft_strlen(bytes);
		//ft_printf("\n%d %d\n", some, len);
		while (i-- > some)
			ft_putchar(' ');
		ft_printf("%d%s", fstat.st_size, "  ");
		get_time(fstat, tmp);
		tmp = tmp->next;
		if(tmp != NULL)
			ft_putchar('\n');
	}
	//free(bytes);
}

int		compare_time(t_dir d1, t_dir d2)
{
	if (d1.time < d2.time)
		return (1);
	else
		return (0);
}

void	ft_print_ls(t_dir *lst, t_inc *inc, char *path)
{
	t_dir	*tmp;

	if (inc->t == 1)
		sort_lst(&lst, compare_time, 0);
	if (inc->r == 1)
		ft_rev_lst(&lst);
	if (inc->rr == 1)
		//ft_putstr(ft_strjoin(path, ":\n"));
		ft_printf("%s:\n", path);
	if (inc->l == 1)
		print_l(lst);
	else
	{
		tmp = lst;
		while (tmp != NULL)
		{
			ft_putstr(tmp->dir);
			tmp = tmp->next;
			if (tmp != NULL)
				ft_putchar('\n');
		}
	}
	ft_putchar('\n');
	if (inc->rr == 1)
	{
		big_r(lst, inc);
//		if (inc->dirp)
//			free(inc->dirp);
	}
	//free_lst(lst);
}

