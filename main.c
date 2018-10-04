/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 02:17:08 by ihuang            #+#    #+#             */
/*   Updated: 2018/10/04 15:05:00 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_ls.h"

t_entry		*mkent(char *path)
{
	struct stat		st;
	t_entry			*t;

	t = (t_entry*)malloc(sizeof(*t));
	t->name = path;
	if (lstat(t->name, &st) == 0)
	{
		t->mode = st.st_mode;
		t->nlink = st.st_nlink;
		t->uid = st.st_uid;
		t->gid = st.st_gid;
		t->size = st.st_size;
		t->mtime = st.st_mtime;
		return (t);
	}
	perror(path);
	return (NULL);
}

void		get_lls(char **av, t_ll **file_ll, t_ll **dir_ll)
{
	t_entry			*ent;

	if (!*av)
	{
		ent = mkent(".");
		*dir_ll = append(*dir_ll, ent, 'n');
		return ;
	}
	else
	{
		while (*av)
		{
			if ((ent = mkent(*av++)) != NULL)
			{
				if (!S_ISDIR(ent->mode))
					*file_ll = append(*file_ll, ent, 'b');
				else if (S_ISDIR(ent->mode))
					*dir_ll = append(*dir_ll, ent, 'n');
			}
		}
	}
}

void		free_filell(t_ll **head)
{
	t_ll			*temp;

	if (*head == NULL)
		return ;
	while (*head)
	{
		temp = (*head)->bottom;
		(*head)->bottom = NULL;
		free((*head)->ent);
		free(*head);
		*head = temp;
	}
}

void		free_dirll(t_ll **head)
{
	t_ll			*temp;

	if (*head == NULL)
		return ;
	while (*head)
	{
		if ((*head)->bottom)
			free_filell(&(*head)->bottom);
		temp = (*head)->next;
		(*head)->next = NULL;
		free((*head)->ent);
		free(*head);
		(*head) = temp;
	}
}

int			main(int ac, char **av)
{
	t_params		*pp;
	t_ll			*file_ll;
	t_ll			*dir_ll;
	char			c;

	file_ll = NULL;
	dir_ll = NULL;
	ac = 0;
	pp = create_params();
	if ((c = get_flags(av, &pp)) != 0)
		printf("b_ls: illegal option -- %c\n", c);
	else
	{
		av += pp->count + 1;
		get_lls(av, &file_ll, &dir_ll);
		print_filell(file_ll, pp);
		print_dirll(dir_ll, file_ll, pp);
		free_filell(&file_ll);
		free_dirll(&dir_ll);
	}
	free(pp);
	return (0);
}
