/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_ls.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 02:17:41 by ihuang            #+#    #+#             */
/*   Updated: 2018/10/04 12:47:00 by ihuang           ###   ########.fr       */
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

typedef struct		s_params
{
	int				lflag;
	int				aflag;
	int				tflag;
	int				rflag;
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
	time_t			mtime;
}					t_entry;

typedef struct		s_ll
{
	t_entry			*ent;
	struct s_ll		*next;
	struct s_ll		*bottom;
}					t_ll;

void				get_lls(char **av, t_ll **file_ll, t_ll **dir_ll);
t_entry				*mkent(char *path);
t_params			*create_params(void);
char				get_flags(char **av, t_params **pp);
t_ll				*create_element(t_entry *ent);
t_ll				*append(t_ll *head, t_entry *ent, char dir);
t_ll				*mk_ll_underdir(t_ll *dir);
void				ls(t_entry *ent, t_params *pp);
long long			get_total(t_ll *head, t_params *p);
void				print_filell(t_ll *head, t_params *p);
void				print_dirll(t_ll *dir_ll, t_ll *file_ll, t_params *p);
int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strlen(const char *s);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *s1);
char				*create_modestring(t_entry *ent, char *mode_string);
size_t				ll_len(t_ll *head, char dir);
void				swap_llentries(t_ll *ptr1, t_ll *ptr2);
void				reverse_ll(t_ll **head, char dir);
t_ll				*sort_updown(t_ll *head, t_params *p);
t_ll				*sort_leftright(t_ll *head, t_params *p);
void				free_filell(t_ll **head);
void				free_dirll(t_ll **head);

#endif
