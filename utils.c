/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 14:40:33 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/27 19:16:31 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strjoinnl(char const *s1, char const *s2)
{
	int		i;
	int		k;
	char	*bruh;

	if (!s1 || !s2)
		return (0);
	i = 0;
	k = 0;
	bruh = (char *)malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 2));
	if (bruh == 0)
		return (0);
	while (s1[i])
	{
		bruh[i] = s1[i];
		i++;
	}
	bruh[i] = '\n';
	i++;
	while (s2[k])
	{
		bruh[i] = s2[k];
		k++;
		i++;
	}
	bruh[i] = '\0';
	return (bruh);
}

char	*ft_strdupnl(char const *s1)
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
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		ft_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || (c == 32))
		return (1);
	else
		return (0);
}