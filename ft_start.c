//
// Created by И Б on 03.05.20.
//

#include "ft_ls.h"

void	get_p(t_dir *tmp, struct stat fstat)
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

void	print_info(t_inc *inc, int flag)
{
	//tmp->dir = ft_strdup(inc->dp->d_name);
	char *str_tmp;

	str_tmp = some_str(inc->lst->dir, inc);
	inc->lst->full_path = str_tmp;
	get_p(inc->lst, inc->sb);
	//ft_putchar(' ');
	ft_putnbr(inc->sb.st_nlink);
	ft_putstr(" ");
	get_user(inc, inc->sb, 1);
	ft_printf(" %d%s", inc->sb.st_size, " ");
	inc->lst->time = inc->sb.st_mtime;
	inc->lst->time_u = inc->sb.st_atime;
	inc->lst->size_f = inc->sb.st_size;
	inc->lst->time_m = inc->sb.st_mtim.tv_nsec;
	inc->lst->time_u_m = inc->sb.st_atim.tv_nsec;
	get_time(inc->sb, inc->lst, inc, flag);
	ft_putchar('\n');
}

int		ft_check(t_inc *inc, char *str)
{
	if ((inc->dirp = opendir(".")) != NULL)
	{
		while ((inc->dp = readdir(inc->dirp)) != NULL)
		{
			lstat(inc->dp->d_name, &inc->sb);
			if (S_ISREG(inc->sb.st_mode) && ft_strcmp(inc->dp->d_name, inc->lst->dir) == 0)
			{
				if (inc->l == 1)
				{
					print_info(inc, 0);
				}
				else
					ft_putendl(inc->dp->d_name);
				return (1);
			}
			else if (!ft_strcmp(inc->dp->d_name, inc->lst->dir))
			{
				ft_putstr("ft_ls: ");
				ft_putstr(inc->lst->dir);
				ft_putendl(": Permission denied");
				return (-1);
			}
		}
		ft_putstr("ft_ls: ");
		ft_putstr(inc->lst->dir);
		ft_putendl(": No such file or directory");
		return (-1);
	}
	return (0);
}

char 	*sek_j(char *s1, char *s2)
{
	return (ft_strjoin(s1, s2));
}

char	*some_str(char *str, t_inc *inc)
{
	char	*tmp;
	char	*res;

	res = str;
	str = ft_strjoin(str, "/");
	//free(res);
	if (inc->dp != NULL)
		tmp = sek_j(str, inc->dp->d_name);
	else
		tmp = sek_j(str, "\0");
	//tmp = ft_strjoin(str, inc->dp->d_name);
	free(str);
	return (tmp);
}

void	do_operation(char *str, t_inc *inc)
{
	t_dir		*lst;
	t_dir		*tmp;
	char 		*str_tmp;
	struct tm	*tm;
	lst = NULL;
//	if (flag == 1)
//		free(inc->dirp);

	if ((inc->dirp = opendir(str)) != NULL) //S_ISLNK(fstat.st_mode)
	{
		while ((inc->dp = readdir(inc->dirp)) != NULL)
		{
			if (inc->dp->d_name[0] != '.' || inc->a == 1)
			{
				tmp = (t_dir *)ft_memalloc(sizeof(t_dir));
				tmp->dir = ft_strdup(inc->dp->d_name);
				str_tmp = some_str(str, inc);
				tmp->full_path = str_tmp;
				lstat(tmp->full_path, &inc->sb);
				tmp->time = inc->sb.st_mtime;
				tmp->time_u = inc->sb.st_atime;
				tmp->size_f = inc->sb.st_size;
				tmp->time_m = inc->sb.st_mtim.tv_nsec;
				tmp->time_u_m = inc->sb.st_atim.tv_nsec;
				(S_ISDIR(inc->sb.st_mode) == 1) ? tmp->true_dir = 100 : 0;
//				tm = localtime(&inc->sb.st_mtime);
//				ft_printf("%d %d %d %d %d %d %d %s!!\n", tm->tm_year + 1900, tm->tm_mon + 1,
//						tm->tm_wday, tm->tm_hour, tm->tm_min, tm->tm_sec, inc->sb.st_mtim.tv_nsec, tmp->dir);
				tmp->next = lst;
				lst = tmp;
			}
		}
		sort_lst(&lst, compare_strs, 0);
		ft_print_ls(&lst, inc, str);
		free_lst(lst);
		//free(inc->dirp);
		//free(str_tmp);
		//free(inc->dirp);
		//free_l(inc);
	}
	else
		ft_check(inc, str);
}

//int 	check_link(t_inc *inc, struct stat fstat)
//{
//	//S_ISDIR(inc->sb.st_mode) == 1
//	int i = 0;
////	(S_ISDIR(fstat.st_mode) == 1) ? i = 1 : 0;
////	ft_printf("%d\n",i);
//	//get_p(inc->lst, fstat);
//	(S_ISLNK(fstat.st_mode) == 1) ? i = 1 : 0;
//	ft_printf("%d\n",i);
//	return 0;
//}

void	ft_ls(t_inc *inc, char *str_tmp) {
	t_dir *tmp;
	//struct stat		fstat;
	int 			i;

	i = 0;
	tmp = inc->lst;
	lstat(tmp->dir, &inc->sb);
	if (inc->l == 1 && (S_ISLNK(inc->sb.st_mode) == 1))
	{

		print_info(inc, 1);
	}
	else
		{
			while (tmp != NULL)
			{
				do_operation(tmp->dir, inc);

				tmp = tmp->next;
			}
		}
	//free(str);

	//free_lst(tmp);
}
//xtr