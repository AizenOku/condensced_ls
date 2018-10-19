/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mkll.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 13:39:41 by ihuang            #+#    #+#             */
/*   Updated: 2018/10/07 15:04:53 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_ls.h"

t_ll	*create_element(t_entry *ent)
{
	t_ll	*list;

	list = (t_ll*)malloc(sizeof(*list));
	list->ent = ent;
	list->next = NULL;
	return (list);
}

t_ll	*append(t_ll *head, t_entry *ent)
{
	t_ll	*temp;
	t_ll	*p;

	temp = create_element(ent);
	if (head == NULL)
		return (temp);
	p = head;
	while (p->next)
		p = p->next;
	p->next = temp;
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
				ll_under = append(ll_under, ent);
			}
			free(path);
		}
		closedir(dirp);
		return (ll_under);
	}
	perror(dir->ent->name);
	return (NULL);
}

void	free_ll(t_ll **head)
{
	t_ll			*temp;

	if (*head == NULL)
		return ;
	while (*head)
	{
		temp = (*head)->next;
		(*head)->next = NULL;
		free((*head)->ent);
		free(*head);
		*head = temp;
	}
}
