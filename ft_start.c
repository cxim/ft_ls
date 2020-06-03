//
// Created by И Б on 03.05.20.
//

#include "ft_ls.h"

int		ft_check(t_inc *inc)
{
	if ((inc->dirp = opendir(".")) != NULL)
	{
		while ((inc->dp = readdir(inc->dirp)) != NULL)
		{
			lstat(inc->dp->d_name, &inc->sb);
			if (S_ISREG(inc->sb.st_mode) && ft_strcmp(inc->dp->d_name, inc->lst->dir) == 0)
			{
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
	tmp = sek_j(str, inc->dp->d_name);
	//tmp = ft_strjoin(str, inc->dp->d_name);
	free(str);
	return (tmp);
}

void	do_operation(char *str, t_inc *inc)
{
	t_dir		*lst;
	t_dir		*tmp;
	char 		*str_tmp;

	lst = NULL;
//	if (flag == 1)
//		free(inc->dirp);
	if ((inc->dirp = opendir(str)) != NULL)
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
				(S_ISDIR(inc->sb.st_mode) == 1) ? tmp->true_dir = 100 : 0;
				tmp->next = lst;
				lst = tmp;

			}

		}

		sort_lst(&lst, compare_strs, 0);
		ft_print_ls(lst, inc, str);

		//free_lst(tmp);
		free_lst(lst);
		//free(inc->dirp);
		//free(str_tmp);
		//free(inc->dirp);
		//free_l(inc);
	}
	else
		ft_check(inc);
}

void	ft_ls(t_inc *inc, char *str_tmp) {
	t_dir *tmp;

	tmp = inc->lst;
	while (tmp != NULL)
	{
		do_operation(tmp->dir, inc);

		tmp = tmp->next;
	}
	//free(str);

	//free_lst(tmp);
}
//xtr