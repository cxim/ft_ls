//
// Created by И Б on 04.05.20.
//

#include "ft_ls.h"

int		compare_strs(t_dir str1, t_dir str2)
{
	return (ft_strcmp(str1.dir, str2.dir));
}

void	sort_lst(t_dir **lst, int (*cmp)(t_dir, t_dir), int i)
{
	t_dir	**src;
	t_dir	*tmp;
	t_dir	*next;

	while (!i && *lst != NULL && (*lst)->next != NULL)
	{
		src = lst;
		tmp = *lst;
		next = (*lst)->next;
		i = 1;
		while (next)
		{
			if (cmp(*tmp, *next) > 0)
			{
				tmp->next = next->next;
				next->next = tmp;
				*src = next;
				i = 0;
			}
			src = &tmp->next;
			tmp = next;
			next = next->next;
		}
	}
}

t_dir 	*ft_rev_lst(t_dir *head)
{
	t_dir	*prev;
	t_dir	*cur;
	t_dir	*next;

	cur = head;
	prev = NULL;
	while (cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	head = prev;
	return (head);
}