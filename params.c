/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 14:12:44 by ihuang            #+#    #+#             */
/*   Updated: 2018/10/02 15:59:13 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_ls.h"

t_params	*create_params(void)
{
	t_params		*p;

	p = (t_params*)malloc(sizeof(t_params));
	p->lflag = 0;
	p->aflag = 0;
	p->tflag = 0;
	p->rflag = 0;
	p->count = 0;
	return (p);
}

char		get_flags(char **av, t_params **pp)
{
	int				j;
	int				i;

	i = 0;
	while (av[++i] && av[i][0] == '-')
	{
		if (av[i][1] == '-' || av[i][1] == '\0')
			return (av[i][1]);
		j = 0;
		while (av[i][++j])
		{
			if (av[i][j] == 'l')
				(*pp)->lflag = 1;
			else if (av[i][j] == 'a')
				(*pp)->aflag = 1;
			else if (av[i][j] == 't')
				(*pp)->tflag = 1;
			else if (av[i][j] == 'r')
				(*pp)->rflag = 1;
			else
				return (av[i][j]);
		}
		(*pp)->count++;
	}
	return (0);
}
