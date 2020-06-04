//
// Created by И Б on 04.05.20.
//

#include "ft_ls.h"

int		compare_strs(t_dir str1, t_dir str2)
{
	int i = 0;
	char 	*st1 = ft_strdup(str1.dir);
	char 	*st2 = ft_strdup(str2.dir);

	while (st1[i] != '\0')
	{
		st1[i] = ft_tolower(st1[i]);
		i++;
	}
	i = 0;
	while (st2[i] != '\0')
	{
		st2[i] = ft_tolower(st2[i]);
		i++;
	}
	int j = ft_strcmp(st1, st2);
	free(st1);
	free(st2);
	return (j);
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

void	ft_rev_lst(t_dir **head)
{
	t_dir	*prev;
	t_dir	*cur;
	t_dir	*next;

	cur = *head;
	prev = NULL;
	while (cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	//free_lst(head);
	*head = prev;
	//return (head);
}
