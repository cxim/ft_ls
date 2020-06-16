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
	int 			d;
	time_t 			time;
	time_t			time_u;
	time_t			time_c;
	ulong 			time_m;
	ulong 			time_u_m;
	ulong 			time_c_m;
	struct s_dir 	*next;
}					t_dir;

typedef struct		s_inc
{
	int				bytes_len;
	int 			links_len;
	int 			owner_name_len;
	int 			group_name_len;
	int 			p;
	int 			l;
	int 			a;
	int 			r;
	int 			t;
	int 			rr;
	int				u;
	int				c;
	int				one;
	int				d;
	int				u_big;
	int 			f_big;
	int				s_big;
	char 			*path;
	char 			*dump_dir;
	char 			*dump_dir_tmp;
	DIR				*dirp;
	struct dirent	*dp;
	struct stat		sb;
	t_dir			*lst;
}					t_inc;

void	ft_ls(t_inc *inc, int flag);
void	ft_print_ls(t_dir **lst, t_inc *inc, char *path);
void	sort_lst(t_dir **lst, int (*cmp)(t_dir, t_dir), int i);
int		compare_strs(t_dir str1, t_dir str2);
void 	ft_rev_lst(t_dir **head);
void	do_operation(char *str, t_inc *inc);
void	free_lst(t_dir *dir);
void	free_l(t_inc *inc);
int		compare_strs(t_dir str1, t_dir str2);
void 	get_user(t_inc *inc, struct stat fstat, int flag);
void	get_time(struct stat fstat, t_dir *tmp, t_inc *inc, int flag);
char	*some_str(char *str, t_inc *inc);
void	get_prem_for_f(char *str, struct stat fstat, t_dir *tmp);
void	print_sign_f(char *path, int flag, t_inc *inc);
char 	*sek_j(char *s1, char *s2);
void	print_sign_ff(char *path, int flag, t_inc *inc);
int 	dir_file(t_inc *inc);
char	*path_link(char *str1, char *str2);
void	get_p(t_dir *tmp, struct stat fstat);
#endif //FT_LS_FT_LS_H
