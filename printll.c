/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printll.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 13:53:34 by ihuang            #+#    #+#             */
/*   Updated: 2018/10/07 14:55:56 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_ls.h"

void		print_filell(t_ll *head, t_params *p)
{
	if (head == NULL)
		return ;
	else
	{
		head = sort_ll(head, p);
		while (head)
		{
			ls(head->ent, p);
			head = head->next;
		}
		printf("\n");
	}
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
	dir_ll = sort_ll(dir_ll, p);
	while (dir_ll)
	{
		temp_head = NULL;
		if (more_than_one || file_ll)
			printf("%s:\n", dir_ll->ent->name);
		temp_head = mk_ll_underdir(dir_ll);
		if (p->lflag && temp_head)
			print_total(temp_head, p);
		if (temp_head)
			print_filell(temp_head, p);
		else if (!temp_head && dir_ll->next)
			printf("\n");
		free_ll(&temp_head);
		dir_ll = dir_ll->next;
	}
}
