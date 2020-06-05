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
	int 			size_f;
	time_t 			time;
	time_t			time_u;
	ulong 			time_m;
	ulong 			time_u_m;
	struct s_dir 	*next;
}					t_dir;

typedef struct		s_inc
{
	int				bytes_len;
	int 			links_len;
	int 			owner_name_len;
	int 			group_name_len;
	int 			l;
	int 			a;
	int 			r;
	int 			t;
	int 			rr;
	int				u;
	int				one;
	int				s_big;
	char 			*path;
	DIR				*dirp;
	struct dirent	*dp;
	struct stat		sb;
	t_dir			*lst;
}					t_inc;

void	ft_ls(t_inc *inc, char *str);
void	ft_print_ls(t_dir **lst, t_inc *inc, char *path);
void	sort_lst(t_dir **lst, int (*cmp)(t_dir, t_dir), int i);
int		compare_strs(t_dir str1, t_dir str2);
void 	ft_rev_lst(t_dir **head);
void	do_operation(char *str, t_inc *inc);
void	free_lst(t_dir *dir);
void	free_l(t_inc *inc);
int		compare_strs(t_dir str1, t_dir str2);
#endif //FT_LS_FT_LS_H
