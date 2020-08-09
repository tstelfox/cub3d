/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_extra.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 18:46:10 by tmullan       #+#    #+#                 */
/*   Updated: 2020/08/09 20:01:34 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_free(char **arroios, int i)
{
	if (arroios[i] == 0)
	{
		while (i > 0)
		{
			i--;
			free(arroios[i]);
		}
		free(arroios);
		return (1);
	}
	return (0);
}

static int	ft_splitlen(const char *s, int len, char a)
{
	int i;

	i = 0;
	if (s[len] == a && s[len + 1] != '\0')
		return (1);
	while (s[len] != '\0' && s[len] != a)
	{
		i++;
		len++;
	}
	return (i);
}

static char	**ft_strings(char const *s, char c, char **arroios, int nos)
{
	int		size;
	int		len;
	int		all;
	int		i;

	i = 0;
	len = 0;
	while (i < nos)
	{
		all = 0;
		s[len] == c ? len++ : len;
		size = ft_splitlen(s, len, c);
		arroios[i] = (char *)malloc(sizeof(char) * (size + 1));
		if (ft_free(arroios, i))
			return (0);
		while (all < size)
		{
			arroios[i][all] = s[len];
			len++;
			all++;
		}
		arroios[i][all] = '\0';
		i++;
	}
	return (arroios);
}

static int	ft_sep(char const *s, char c)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
		{
			if (s[i] == c && s[i + 1] == c)
				count++;
			i++;
		}
		if (s[i])
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

char		**ft_split_extra(char const *s, char c)
{
	int		i;
	int		t;
	int		nos;
	char	**arroios;

	i = 0;
	t = 0;
	if (s == 0)
		return (0);
	nos = ft_sep(s, c);
	arroios = (char **)malloc(sizeof(char *) * (nos + 1));
	if (arroios == 0)
		return (0);
	arroios = ft_strings(s, c, arroios, nos);
	if (arroios == 0)
		return (0);
	arroios[nos] = NULL;
	return (arroios);
}
