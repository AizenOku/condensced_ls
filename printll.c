/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printll.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 13:53:34 by ihuang            #+#    #+#             */
/*   Updated: 2018/10/04 11:52:21 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_ls.h"

char		*create_modestring(t_entry *ent, char *mode)
{
	mode[10] = '\0';
	if (S_ISLNK(ent->mode))
		*mode = 'l';
	else if (S_ISDIR(ent->mode))
		*mode = 'd';
	else
		*mode = '-';
	*++mode = ((ent->mode & S_IRUSR) ? 'r' : '-');
	*++mode = ((ent->mode & S_IWUSR) ? 'w' : '-');
	*++mode = ((ent->mode & S_IXUSR) ? 'x' : '-');
	*++mode = ((ent->mode & S_IRGRP) ? 'r' : '-');
	*++mode = ((ent->mode & S_IWGRP) ? 'w' : '-');
	*++mode = ((ent->mode & S_IXGRP) ? 'x' : '-');
	*++mode = ((ent->mode & S_IROTH) ? 'r' : '-');
	*++mode = ((ent->mode & S_IWOTH) ? 'w' : '-');
	*++mode = ((ent->mode & S_IXOTH) ? 'x' : '-');
	*++mode = '\0';
	return (mode - 10);
}

void		ls(t_entry *ent, t_params *pp)
{
	char			*ptr;
	struct group	*gr;
	struct passwd	*pw;

	ptr = NULL;
	if (!(pp->aflag) && *(ent->name) == '.')
		return ;
	else if (!(pp->lflag))
		printf("%s\n", ent->name);
	else
	{
		ptr = (char*)malloc(sizeof(char) * 10);
		printf("%s", create_modestring(ent, ptr));
		free(ptr);
		printf("%3d ", ent->nlink);
		if ((pw = getpwuid(ent->uid)))
			printf("%s  ", pw->pw_name);
		if ((gr = getgrgid(ent->gid)))
			printf("%s  %5lld ", gr->gr_name, ent->size);
		ptr = ctime(&ent->mtime) + 4;
		printf("%.12s ", ptr);
		printf("%s\n", ent->name);
	}
}

long long	get_total(t_ll *head, t_params *p)
{
	long long		total;
	int				addextra;

	total = 0;
	while (head)
	{
		addextra = 0;
		if (!p->aflag && *(head->ent->name) == '.')
		{
			head = head->bottom;
			continue ;
		}
		if (head->ent->size % 512 != 0)
			addextra = 1;
		total += head->ent->size / 512 + addextra;
		head = head->bottom;
	}
	return (total);
}

void		print_filell(t_ll *head, t_params *p)
{
	t_ll			*temp;
	unsigned int	count;

	count = 0;
	if (head == NULL)
		return ;
	head = sort_updown(head, p);
	if (p->rflag)
		reverse_ll(&head, 'b');
	while (head)
	{
		ls(head->ent, p);
		temp = head;
		head = head->bottom;
		temp->bottom = NULL;
	}
	printf("\n");
}

void		print_dirll(t_ll *dir_ll, t_ll *file_ll, t_params *p)
{
	int				more_than_one;
	t_ll			*temp_head;

	if (dir_ll == NULL)
		return ;
	more_than_one = 0;
	if (dir_ll->next)
		more_than_one = 1;
	dir_ll = sort_leftright(dir_ll, p);
	if (p->rflag)
		reverse_ll(&dir_ll, 'n');
	while (dir_ll)
	{
		temp_head = NULL;
		if (more_than_one || file_ll)
			printf("%s:\n", dir_ll->ent->name);
		temp_head = mk_ll_underdir(dir_ll);
		if (p->lflag && temp_head)
			printf("total: %lld\n", get_total(temp_head, p));
		if (temp_head)
			print_filell(temp_head, p);
		else
			printf("\n");
		dir_ll = dir_ll->next;
	}
}
