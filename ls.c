/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:59:25 by ihuang            #+#    #+#             */
/*   Updated: 2018/10/07 15:33:18 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_ls.h"

void		ls(t_entry *ent, t_params *pp)
{
	char			*buf;
	struct group	*gr;
	struct passwd	*pw;

	if ((!pp->aflag) && *(ent->name) == '.')
		return ;
	if (pp->lflag)
	{
		buf = (char*)malloc(sizeof(char) * 200);
		printf("%s ", create_modestring(ent, buf));
		printf("%3d ", ent->nlink);
		if ((pw = getpwuid(ent->uid)))
			printf("%s  ", pw->pw_name);
		if ((gr = getgrgid(ent->gid)))
			printf("%s  %5lld ", gr->gr_name, ent->size);
		print_time(ent->mtimespec);
		free(buf);
	}
	printf("%s", ent->name);
	if (pp->lflag && S_ISLNK(ent->mode))
		print_path(ent->name);
	printf("\n");
}

char		*create_modestring(t_entry *ent, char *mode)
{
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

void		print_total(t_ll *head, t_params *p)
{
	long long	total;

	total = 0;
	while (head)
	{
		if (!p->aflag && *(head->ent->name) == '.')
		{
			head = head->next;
			continue ;
		}
		total += head->ent->blocks;
		head = head->next;
	}
	if (total)
		printf("total %lld\n", total);
}

void		print_path(char *path)
{
	char			*buf;
	int				len;

	len = 0;
	if ((buf = (char*)malloc(sizeof(char) * 200)) != NULL)
	{
		if ((len = readlink(path, buf, 200)) != -1)
		{
			*(buf + len) = '\0';
			printf(" -> %s", buf);
		}
		free(buf);
	}
	else
		perror(path);
}

void		print_time(struct timespec ts)
{
	char		*s;

	if (time(NULL) > ts.tv_sec + (180 * 24 * 60 * 60) || \
			time(NULL) < ts.tv_sec)
	{
		s = ctime(&(ts.tv_sec)) + 4;
		printf("%.6s  ", s);
		s += 16;
		printf("%.4s ", s);
	}
	else
	{
		s = ctime(&(ts.tv_sec)) + 4;
		printf("%.12s ", s);
	}
}
