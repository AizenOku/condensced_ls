/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 13:27:10 by ihuang            #+#    #+#             */
/*   Updated: 2018/10/04 11:51:47 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_ls.h"

size_t	ft_strlen(const char *s)
{
	char			*p;

	p = (char*)s;
	while (*p)
		p++;
	return (p - s);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	c1;
	unsigned char	c2;

	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	c1 = *s1;
	c2 = *s2;
	return (c1 - c2);
}

char	*ft_strcpy(char *dst, const char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strcat(char *s1, const char *s2)
{
	size_t			s1_len;
	size_t			s2_len;
	char			*p;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	p = s1 + s1_len;
	while (*s2)
		*p++ = *s2++;
	*p = '\0';
	return (s1);
}

char	*ft_strdup(const char *s1)
{
	char		*str2;
	size_t		i;
	size_t		n;

	n = ft_strlen(s1);
	if (!(str2 = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	i = 0;
	while (i < n)
	{
		str2[i] = s1[i];
		i++;
	}
	str2[i] = '\0';
	return ((char *)str2);
}
