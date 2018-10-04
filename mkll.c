/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mkll.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 13:39:41 by ihuang            #+#    #+#             */
/*   Updated: 2018/10/02 14:13:40 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_ls.h"

t_ll	*create_element(t_entry *ent)
{
	t_ll	*list;

	list = (t_ll*)malloc(sizeof(*list));
	list->ent = ent;
	list->next = NULL;
	list->bottom = NULL;
	return (list);
}

t_ll	*append(t_ll *head, t_entry *ent, char dir)
{
	t_ll	*new;
	t_ll	*p;

	new = create_element(ent);
	if (head == NULL)
		return (new);
	p = head;
	if (dir == 'b')
	{
		while (p->bottom)
			p = p->bottom;
		p->bottom = new;
	}
	else if (dir == 'n')
	{
		while (p->next)
			p = p->next;
		p->next = new;
	}
	else
		return (NULL);
	return (head);
}

t_ll	*mk_ll_underdir(t_ll *dir)
{
	DIR				*dirp;
	struct dirent	*direntp;
	t_ll			*ll_under;
	t_entry			*ent;
	char			*path;

	if ((dirp = opendir(dir->ent->name)))
	{
		ll_under = NULL;
		while ((direntp = readdir(dirp)) != NULL)
		{
			path = (char*)malloc(sizeof(char) * 100);
			path = ft_strcat(ft_strcpy(path, dir->ent->name), "/");
			if ((ent = mkent(ft_strcat(path, direntp->d_name))) != NULL)
			{
				ent->name = ft_strdup(direntp->d_name);
				ll_under = append(ll_under, ent, 'b');
			}
			free(path);
		}
		closedir(dirp);
		return (ll_under);
	}
	perror(dir->ent->name);
	return (NULL);
}
