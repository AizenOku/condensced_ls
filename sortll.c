/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 13:47:53 by ihuang            #+#    #+#             */
/*   Updated: 2018/10/02 13:57:19 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_ls.h"

size_t		ll_len(t_ll *head, char dir)
{
	size_t			len;

	len = 0;
	if (dir == 'b')
	{
		while (head)
		{
			len++;
			head = head->bottom;
		}
	}
	else if (dir == 'n')
	{
		while (head)
		{
			len++;
			head = head->next;
		}
	}
	return (len);
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

void		reverse_ll(t_ll **head, char dir)
{
	t_ll			*curr;
	t_ll			*next;
	t_ll			*prev;

	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (dir == 'b')
		{
			next = curr->bottom;
			curr->bottom = prev;
		}
		else
		{
			next = curr->next;
			curr->next = prev;
		}
		prev = curr;
		curr = next;
	}
	*head = prev;
}

t_ll		*sort_updown(t_ll *head, t_params *p)
{
	t_ll			*start;
	t_ll			*ptr;
	t_ll			*most;

	start = head;
	while (start->bottom)
	{
		most = start;
		ptr = start->bottom;
		while (ptr)
		{
			if (p->tflag)
			{
				if (ptr->ent->mtime > most->ent->mtime)
					most = ptr;
			}
			else if (ft_strcmp(ptr->ent->name, most->ent->name) < 0)
				most = ptr;
			ptr = ptr->bottom;
		}
		swap_llentries(start, most);
		start = start->bottom;
	}
	return (head);
}

t_ll		*sort_leftright(t_ll *head, t_params *p)
{
	t_ll			*start;
	t_ll			*ptr;
	t_ll			*most;

	start = head;
	while (start->next)
	{
		most = start;
		ptr = start->next;
		while (ptr)
		{
			if (p->tflag)
			{
				if (ptr->ent->mtime > most->ent->mtime)
					most = ptr;
			}
			else if (ft_strcmp(ptr->ent->name, most->ent->name) < 0)
				most = ptr;
			ptr = ptr->next;
		}
		swap_llentries(start, most);
		start = start->next;
	}
	return (head);
}
