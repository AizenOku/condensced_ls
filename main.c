/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 02:17:08 by ihuang            #+#    #+#             */
/*   Updated: 2018/10/07 15:02:26 by ihuang           ###   ########.fr       */
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
		t->mtimespec = st.st_mtimespec;
		t->blocks = st.st_blocks;
	}
	else
	{
		perror(path);
		t = NULL;
		free(t);
	}
	return (t);
}

void		get_lls(char **av, t_ll **file_ll, t_ll **dir_ll)
{
	t_entry			*ent;

	if (!*av)
	{
		ent = mkent(".");
		*dir_ll = append(*dir_ll, ent);
	}
	else
	{
		while (*av)
		{
			if ((ent = mkent(*av++)) != NULL)
			{
				if (!S_ISDIR(ent->mode))
					*file_ll = append(*file_ll, ent);
				else if (S_ISDIR(ent->mode))
					*dir_ll = append(*dir_ll, ent);
			}
		}
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
	pp = initiate_params();
	if ((c = get_params(av, &pp)) == 0)
	{
		av += pp->count + 1;
		get_lls(av, &file_ll, &dir_ll);
		print_filell(file_ll, pp);
		print_dirll(dir_ll, file_ll, pp);
		free_ll(&file_ll);
		free_ll(&dir_ll);
	}
	else
		printf("b_ls: illegal option -- %c\n", c);
	free(pp);
	return (0);
}
