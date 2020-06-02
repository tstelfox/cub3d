/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 13:21:36 by tmullan        #+#    #+#                */
/*   Updated: 2020/01/10 21:48:30 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		k;
	char	*bruh;

	if (!s1 || !s2)
		return (0);
	i = 0;
	k = 0;
	bruh = (char *)malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (bruh == 0)
		return (0);
	while (s1[i])
	{
		bruh[i] = s1[i];
		i++;
	}
	while (s2[k] && s2[k] != '\n')
	{
		bruh[i] = s2[k];
		k++;
		i++;
	}
	bruh[i] = '\0';
	free(s1);
	return (bruh);
}

size_t	ft_strlen(char *s)
{
	size_t c;

	c = 0;
	while (s[c])
		c++;
	return (c);
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*dup;

	i = 0;
	while (s1[i])
		i++;
	dup = (char *)malloc(sizeof(char) * (i + 1));
	if (dup == 0)
		return (0);
	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	*ft_memmove(void *dst, void *src, size_t len)
{
	char		*adst;
	char		*asrc;
	size_t		i;

	adst = (char *)dst;
	asrc = (char *)src;
	i = 0;
	if (!src && !dst)
		return (0);
	if (src >= dst)
	{
		while (i < len)
		{
			adst[i] = asrc[i];
			i++;
		}
		len = 0;
	}
	while (len > 0)
	{
		len--;
		adst[len] = asrc[len];
	}
	return (dst);
}
