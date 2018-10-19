/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 13:47:53 by ihuang            #+#    #+#             */
/*   Updated: 2018/10/07 15:17:11 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_ls.h"

t_ll		*compare_time(t_ll *ptr, t_ll *most)
{
	t_ll			*ret;

	if (ptr->ent->mtimespec.tv_sec > most->ent->mtimespec.tv_sec)
		ret = ptr;
	else if (ptr->ent->mtimespec.tv_sec < most->ent->mtimespec.tv_sec)
		ret = most;
	else
	{
		if (ptr->ent->mtimespec.tv_nsec > most->ent->mtimespec.tv_nsec)
			ret = ptr;
		else
			ret = most;
	}
	return (ret);
}

void		swap_llentries(t_ll *ptr1, t_ll *ptr2)
{
	t_entry			*temp;

	if (ptr1 == ptr2)
		return ;
	temp = ptr1->ent;
	ptr1->ent = ptr2->ent;
	ptr2->ent = temp;
}

void		reverse_ll(t_ll **head)
{
	t_ll			*curr;
	t_ll			*next;
	t_ll			*prev;

	curr = *head;
	prev = NULL;
	next = NULL;
	if (!*head)
		return ;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
}

t_ll		*sort_ll(t_ll *head, t_params *p)
{
	t_ll			*start;
	t_ll			*ptr;
	t_ll			*most;

	if (head == NULL)
		return (NULL);
	start = head;
	while (start->next)
	{
		most = start;
		ptr = start;
		while (ptr)
		{
			if (p->tflag)
				most = compare_time(ptr, most);
			else if (ft_strcmp(ptr->ent->name, most->ent->name) < 0)
				most = ptr;
			ptr = ptr->next;
		}
		swap_llentries(start, most);
		start = start->next;
	}
	if (p->rflag)
		reverse_ll(&head);
	return (head);
}
