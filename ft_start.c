//
// Created by И Б on 03.05.20.
//

#include "ft_ls.h"
#include <sys/types.h>

char	*some_str_two(char *str, t_inc *inc)
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
void	print_info_two(t_dir *dir, int flag, t_inc *inc)
{
	//tmp->dir = ft_strdup(inc->dp->d_name);
	char *str_tmp;
	char 	str[100];
	int 	len;
	struct stat fstat;
	t_inc *new;

	new = (t_inc*)ft_memalloc(sizeof(t_inc));
	lstat(dir->dir, &fstat);
	str_tmp = some_str(dir->dir, inc);
	dir->full_path = str_tmp;
	if (inc->d == 1)
		get_p(dir, 1);
	else
		get_p(dir, 0);
	//ft_putchar(' ');
	ft_putnbr(fstat.st_nlink); //zero = 261 ; 2697
	ft_putstr(" ");
	get_user(new, fstat, 1);
	if (S_ISCHR(fstat.st_mode) != 0 || S_ISBLK(fstat.st_mode))
	{
		ft_printf(" %d, %d ", MAJOR(fstat.st_rdev),  MINOR(fstat.st_rdev));
	}
	else
		ft_printf(" %d%s", fstat.st_size, " ");
	dir->time = fstat.st_mtime;
	dir->time_u = fstat.st_atime;
	dir->size_f = fstat.st_size;
	dir->time_m = fstat.st_mtimespec.tv_nsec;
	dir->time_u_m = fstat.st_atimespec.tv_nsec;
	get_time(fstat, dir, inc, flag);
	if (inc->f_big == 1)
	{
		if (S_ISLNK(fstat.st_mode))
		{
//			len = readlink(inc->dump_dir, str, 100);
//			str[len] = '\0';
//			str = path_link(inc->dump_dir, inc->dump_dir_tmp);
//			free(inc->lst->full_path);
//			inc->lst->full_path = ft_strdup(str);
			print_sign_ff(dir->dir, 2, inc);
			//free(str);
			free(inc->dump_dir_tmp);
		}
		else
		{
			get_prem_for_f(dir->dir, fstat, dir);
			free(inc->dump_dir_tmp);
		}
	}
	ft_putchar('\n');
	free_l(new);
	free(str_tmp);
}

void	get_p(t_dir *tmp, int flag)
{
	struct stat fstat;

	if (lstat(tmp->dir, &fstat) != -1)
	{
		if (S_ISFIFO(fstat.st_mode))
			ft_putchar('p');
		else if (tmp->true_dir && (S_ISFIFO(fstat.st_mode) != 0))
			ft_putchar('d');
		else if (S_ISDIR(fstat.st_mode) && flag == 1)
			ft_putchar('d');
		else if (S_ISCHR(fstat.st_mode))
			ft_putchar('c');
		else if (S_ISBLK(fstat.st_mode))
			ft_putchar('b');
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
//		ft_putchar(getxattr(tmp->full_path, tmp->dir, NULL, 0) ? '+' : ' ');
		ft_putstr(" "); // 1 || 2?
	}
}

void	print_info(t_inc *inc, int flag)
{
	//tmp->dir = ft_strdup(inc->dp->d_name);
	char *str_tmp;
	char 	str[100];
	int 	len;

	str_tmp = some_str(inc->lst->dir, inc);
	inc->lst->full_path = str_tmp;
	get_p(inc->lst, 0);
	//ft_putchar(' ');
	ft_putnbr(inc->sb.st_nlink);
	ft_putstr(" ");
	get_user(inc, inc->sb, 1);
	ft_printf(" %d%s", inc->sb.st_size, " ");
	inc->lst->time = inc->sb.st_mtime;
	inc->lst->time_u = inc->sb.st_atime;
	inc->lst->size_f = inc->sb.st_size;
	inc->lst->time_m = inc->sb.st_mtimespec.tv_nsec;
	inc->lst->time_u_m = inc->sb.st_atimespec.tv_nsec;
	get_time(inc->sb, inc->lst, inc, flag);
	if (inc->f_big == 1)
	{
		if (S_ISLNK(inc->sb.st_mode))
		{
//			len = readlink(inc->dump_dir, str, 100);
//			str[len] = '\0';
//			str = path_link(inc->dump_dir, inc->dump_dir_tmp);
//			free(inc->lst->full_path);
//			inc->lst->full_path = ft_strdup(str);
			print_sign_ff(inc->dump_dir, 2, inc);
			//free(str);
			free(inc->dump_dir_tmp);
		}
		else
		{
			get_prem_for_f(inc->lst->dir, inc->sb, inc->lst);
			free(inc->dump_dir_tmp);
		}
	}
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
		ft_putstr("/bin/ls: "); //потом исправить как фт_лс
		ft_putstr("cannot access '");
		ft_putstr(inc->lst->dir);
		ft_putendl("': No such file or directory");
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
				if (str)
					tmp->name_dir = ft_strdup(str);
				str_tmp = some_str(str, inc);
				tmp->full_path = str_tmp;
				lstat(tmp->full_path, &inc->sb);
				tmp->time = inc->sb.st_mtime;
				tmp->time_u = inc->sb.st_atime;
				tmp->time_c = inc->sb.st_ctime;
				tmp->size_f = inc->sb.st_size;
				tmp->time_m = inc->sb.st_mtimespec.tv_nsec;
				tmp->time_u_m = inc->sb.st_atimespec.tv_nsec;
				tmp->time_c_m = inc->sb.st_ctimespec.tv_nsec;
				(S_ISDIR(inc->sb.st_mode) == 1) ? tmp->true_dir = 100 : 0;
//				tm = localtime(&inc->sb.st_mtime);
//				ft_printf("%d %d %d %d %d %d %d %s!!\n", tm->tm_year + 1900, tm->tm_mon + 1,
//						tm->tm_wday, tm->tm_hour, tm->tm_min, tm->tm_sec, inc->sb.st_mtim.tv_nsec, tmp->dir);
				tmp->next = lst;
				lst = tmp;
			}
		}
		if (inc->u_big == 0)
			sort_lst(&lst, compare_strs, 0);
		ft_print_ls(&lst, inc, str);
		free_lst(lst);
//		if (inc->rr == 0)
//			closedir(inc->dirp);
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

/*S_ISFIFO(mode) 	FIFO
S_ISCHR(mode) 	Специальный файл символьного устройства
S_ISDIR(mode) 	Каталог
S_ISBLK(mode) 	Специальный файл блочного устройства
S_ISREG(mode) 	Обычный файл
S_ISLNK(mode) 	Символическая связь
S_ISSOCK(mode) 	Сокет*/

int		get_exec(struct stat fstat)
{
	if (fstat.st_mode & S_IXUSR)
		return (1);
	if (fstat.st_mode & S_IXGRP)
		return  (1);
	if (fstat.st_mode & S_IXOTH)
		return (1);
	return (0);
}
void	print_sign_ff(char *path, int flag, t_inc *inc)
{
	struct stat		sa;
	DIR *tmp;

	tmp = NULL;
	if (path && stat(path, &sa) != -1)
	{
		if (flag == 2)
		{
//			if ((tmp = opendir(path)) != NULL)
//			{
//				ft_putchar('/');
//				closedir(tmp);
//			}
			if (S_ISFIFO(sa.st_mode) != 0 && inc->p != 2)
				ft_putchar('|');
			else if (S_ISDIR(sa.st_mode) != 0 && inc->p != 2)
				ft_putchar('/');
			else if (get_exec(sa) && !S_ISDIR(sa.st_mode) && inc->p != 2)
				ft_putchar('*');

		}
		else
		{
			if (S_ISFIFO(sa.st_mode) != 0 && inc->p != 2)
				ft_putchar('|');
			else if (S_ISLNK(sa.st_mode) != 0 && inc->p != 2)
				ft_putchar('@');
			else if (get_exec(sa) && !S_ISDIR(sa.st_mode) && inc->p != 2)
				ft_putchar('*');
			else if (S_ISDIR(sa.st_mode) != 0 && flag == 1 && inc->p != 2)
				ft_putchar('/');
		}
	}
}

void	print_sign_f(char *path, int flag, t_inc *inc)
{
	struct stat		sb;

	lstat(path, &sb);
	if (S_ISFIFO(sb.st_mode) != 0 && inc->p != 2)
		ft_putchar('|');
	else if (S_ISLNK(sb.st_mode) != 0 && inc->p != 2)
		ft_putchar('@');
	else if (get_exec(sb) && !S_ISDIR(sb.st_mode) && inc->p != 2)
		ft_putchar('*');
	else if (S_ISDIR(sb.st_mode) != 0 && (flag == 1 || inc->d == 1))
		ft_putchar('/');
}

void	ft_ls(t_inc *inc, int flag) {
	t_dir *tmp;
	t_inc *inc_tmp;
	int 			i;

	i = 0;
	//sort_lst(&inc->lst, compare_strs, 0);
	tmp = inc->lst;
	lstat(tmp->dir, &inc->sb);
	if (inc->d == 1 && tmp->type == 1)
	{
		sort_lst(&inc->lst, compare_strs, 0);
		tmp = inc->lst;
		while (tmp != NULL)
		{
			if (inc->l == 1)
			{
				if (inc->f_big == 1)
					tmp->d = 1;
				tmp->true_dir = 0;
				print_info_two(tmp, 1, inc);

			}
			else if (inc->l == 0)
			{
				ft_printf("%s", tmp->dir);
				if (inc->f_big == 1)
					print_sign_f(tmp->dir, 0, inc);
				ft_putchar('\n');
			}
			tmp = tmp->next;
		}
		free_lst(tmp);
	}
//	else if (flag == 1) // flag == 1 dir path
//	{
////		sort_lst(&inc->lst, compare_strs, 0);
//		tmp = inc->lst;
//		while (tmp != NULL)
//		{
//			if (inc->l == 1)
//				print_info_two(tmp, 1, inc);
//			else if (inc->l == 0)
//			{
//				ft_putstr(tmp->dir);
//				if (inc->f_big == 1)
//					print_sign_f(tmp->dir, 0, inc);
//				ft_putchar('\n');
//			}
//			tmp = tmp->next;
//		}
//	}
	else if (tmp->type == 0 || tmp->type == 1 || tmp->type == -1)
	{
		inc_tmp = inc; //???
		while (tmp != NULL)
		{
			if (tmp->type == 0 && flag != 1)
			{
				if (inc->l == 1)
					print_info_two(tmp, 1, inc);
				else if (inc->l == 0)
				{
					ft_putstr(tmp->dir);
					if (inc->f_big == 1)
						print_sign_f(tmp->dir, 0, inc);
					ft_putchar('\n');
				}
			}
			else if (tmp->type == -1)
			{
				ft_putstr_fd("/bin/ls: ", 2); //потом исправить как фт_лс
				ft_putstr_fd("cannot access '", 2);
				ft_putstr_fd(tmp->dir, 2);
				ft_putendl_fd("': No such file or directory", 2);
			}
			else
			{
				do_operation(tmp->dir, inc_tmp);
				if (tmp != NULL) {
					closedir(inc_tmp->dirp);
					//ft_putchar('\n'); //временно и решить проблему с R \n
				}
			}
			tmp = tmp->next;
		}
	}
	else
		ft_check(inc, tmp->dir);
}
//xtr