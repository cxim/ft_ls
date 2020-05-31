//
// Created by И Б on 03.05.20.
//

#ifndef FT_LS_FT_LS_H
#define FT_LS_FT_LS_H

#include "ft_printf/includes/printf.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <limits.h>

typedef struct		s_dir
{
	char 			*dir;
	int 			true_dir;
	char 			*full_path;
	char 			*some;
	time_t 			time;
	struct s_dir 	*next;
}					t_dir;

typedef struct		s_inc
{
	int 			l;
	int 			a;
	int 			r;
	int 			t;
	int 			rr;
	char 			*path;
	DIR				*dirp;
	struct dirent	*dp;
	struct stat		sb;
	t_dir			*lst;
}					t_inc;

void	ft_ls(t_inc *inc, char *str);
void	ft_print_ls(t_dir *lst, t_inc *inc, char *path, char *str_tmp);
void	sort_lst(t_dir **lst, int (*cmp)(t_dir, t_dir), int i);
int		compare_strs(t_dir str1, t_dir str2);
void	ft_rev_lst(t_dir **head);
void	do_operation(char *str, t_inc *inc, char *str_tmp);
void	free_lst(t_dir *dir);
#endif //FT_LS_FT_LS_H
