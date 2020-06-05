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

void	print_ow_gr(char *name, char *g_name, t_inc *inc)
{
	int		i;

	ft_putstr(name);
	if (ft_strlen(name) < inc->owner_name_len)
	{
		i = inc->owner_name_len + 1;
		while (ft_strlen(name) < --i)
			ft_putchar(' ');
	}
	ft_putchar(' ');
	ft_putstr(g_name);
	if (ft_strlen(g_name) < inc->group_name_len)
	{
		i = inc->group_name_len + 1;
		while (ft_strlen(g_name) < --i)
			ft_putchar(' ');
	}
}

void 	get_user(t_inc *inc, struct stat fstat, int flag)
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
	if (flag == 0)
	{
		if (ft_strlen(name) > inc->owner_name_len)
			inc->owner_name_len = ft_strlen(name);
		if (ft_strlen(name_g) > inc->group_name_len)
			inc->group_name_len = ft_strlen(name_g);
	}
	else
		print_ow_gr(name, name_g, inc);
}

void	get_permission(t_dir *tmp, struct stat fstat)
{
	if (tmp->true_dir)
		ft_putchar('d');
	else
		ft_putchar((S_ISLNK(fstat.st_mode)) ? 'l' : '-');
	ft_putchar((fstat.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((fstat.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((fstat.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((fstat.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((fstat.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((fstat.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((fstat.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((fstat.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((fstat.st_mode & S_IXOTH) ? 'x' : '-');
	ft_putstr(" "); // 1 || 2?
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
	while (num >= 10 || num <= -10)
	{
		num =num / 10;
		count++;
	}
	return (count);
}

void	get_lens(t_dir *dir, t_inc *inc)
{
	t_dir			*tmp;
	struct stat		fstat;

	tmp = dir;
	while (tmp != NULL)
	{
		lstat(tmp->full_path, &fstat);
		if (num_len(fstat.st_nlink) > inc->links_len)
			inc->links_len = num_len(fstat.st_nlink);
		get_user(inc, fstat, 0);
		if (num_len(fstat.st_size) > inc->bytes_len)
			inc->bytes_len = num_len(fstat.st_size);
		tmp = tmp->next;
	}
}

void	print_l(t_dir *lst, t_inc *inc)
{
	t_dir			*tmp;
	struct stat		fstat;
	//char 			*bytes;
	int 			len;
	int 			i;
	int				some;

	tmp = lst;
	print_blocks(tmp);
	get_lens(tmp, inc);
//	if (inc->u == 1)
//		sort_lst(&tmp, compare_time_u, 0);
	while (tmp != NULL)
	{
		lstat(tmp->full_path, &fstat);
		get_permission(tmp, fstat);
		if (num_len(fstat.st_nlink) < inc->links_len)  // num links
		{
			i = inc->links_len + 1;
			while (num_len(fstat.st_nlink) < --i)
				ft_putchar(' ');
		}
		ft_putnbr(fstat.st_nlink);
		ft_putstr(" ");
		get_user(inc, fstat, 1);
		ft_putstr(" ");
		i = inc->bytes_len;
		//bytes = ft_itoa(fstat.st_size);
		some = num_len(fstat.st_size);
		//len = ft_strlen(bytes);
		//ft_printf("\n%d %d\n", some, len);
		while (i-- > some)
			ft_putchar(' ');
		ft_printf("%d%s", fstat.st_size, " ");
		get_time(fstat, tmp);
		tmp = tmp->next;
		if(tmp != NULL)
			ft_putchar('\n');
	}
	//free(bytes);
}

int		compare_str(t_dir str1, t_dir str2)
{
	return (ft_strcmp(str1.dir, str2.dir));
}

int		compare_size(t_dir d1, t_dir d2)
{
	if (d1.size_f < d2.size_f)
		return (1);
	else if (d1.size_f == d2.size_f)
		return (compare_strs(d1, d2));
	else
		return (0);
}

int		compare_time(t_dir d1, t_dir d2)
{
	if (d1.time < d2.time)
		return (1);
	else if (d1.time == d2.time)
	{
		if (d1.time_m < d2.time_m)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int		compare_time_u(t_dir d1, t_dir d2)
{
	if (d1.time_u < d2.time_u)
		return (1);
//	else if (d1.time_u == d2.time_u)
//	{
//		if (d1.time_u_m < d2.time_u_m)
//			return (1);
//		else
//			return (0);
//	}
	else
		return (0);
}


// У ВАС ОН БУДЕТ ЗА КРУГОМ ТОЛЬКО

void	ft_print_ls(t_dir **lst, t_inc *inc, char *path)
{
	t_dir	*tmp;

	if (inc->t == 1)
		sort_lst(lst, compare_time, 0);
	if (inc->u == 1 && inc->l == 0)
		sort_lst(lst, compare_time_u, 0);
	if (inc->u == 1 && inc->l == 1 && inc->t == 0)
		sort_lst(lst, compare_str, 0);
	if (inc->r == 1)
		ft_rev_lst(lst);
	if (inc->rr == 1)
		ft_printf("%s:\n", path);
	if (inc->s_big == 1)
		sort_lst(lst, compare_size, 0);
	if (inc->l == 1)
		print_l(*lst, inc);
	else
	{
		tmp = *lst;
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
		big_r(*lst, inc);
//		if (inc->dirp)
//			free(inc->dirp);
	}
	//free_lst(lst);
}

