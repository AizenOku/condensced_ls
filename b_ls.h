/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_ls.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 02:17:41 by ihuang            #+#    #+#             */
/*   Updated: 2018/10/07 14:46:47 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef B_LS_H
# define B_LS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>

typedef struct		s_params
{
	int				lflag;
	int				aflag;
	int				tflag;
	int				rflag;
	int				fflag;
	int				count;
}					t_params;

typedef struct		s_entry
{
	char			*name;
	mode_t			mode;
	nlink_t			nlink;
	uid_t			uid;
	gid_t			gid;
	off_t			size;
	struct timespec mtimespec;
	quad_t			blocks;
}					t_entry;

typedef struct		s_ll
{
	t_entry			*ent;
	struct s_ll		*next;
}					t_ll;

void				get_lls(char **av, t_ll **file_ll, t_ll **dir_ll);
t_entry				*mkent(char *path);
t_params			*initiate_params(void);
char				get_params(char **av, t_params **pp);
void				add_param(char c, t_params *p_);
t_ll				*create_element(t_entry *ent);
t_ll				*append(t_ll *head, t_entry *ent);
t_ll				*mk_ll_underdir(t_ll *dir);
void				ls(t_entry *ent, t_params *pp);
void				print_total(t_ll *head, t_params *p);
void				print_filell(t_ll *head, t_params *p);
void				print_dirll(t_ll *dir_ll, t_ll *file_ll, t_params *p);
int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strlen(const char *s);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *s1);
char				*ft_strchr(const char *s, char c);
char				*create_modestring(t_entry *ent, char *mode_string);
void				swap_llentries(t_ll *ptr1, t_ll *ptr2);
void				reverse_ll(t_ll **head);
t_ll				*sort_ll(t_ll *head, t_params *p);
void				free_ll(t_ll **head);
t_ll				*compare_time(t_ll *ptr, t_ll *most);
void				print_path(char *path);
void				print_time(struct timespec ts);

#endif
