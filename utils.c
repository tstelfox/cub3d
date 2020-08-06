/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 14:40:33 by tmullan       #+#    #+#                 */
/*   Updated: 2020/08/06 17:43:43 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char		*ft_strjoinnl(char *s1, char *s2, int i, int k)
{
	char	*bruh;

	if (!s1 || !s2)
		return (0);
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
	while (s2[k] != '\0')
	{
		bruh[i] = s2[k];
		k++;
		i++;
	}
	free(s1);
	bruh[i] = '\0';
	return (bruh);
}

char		*ft_strdupnl(char const *s1)
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

int			ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int			ft_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || (c == 32))
		return (1);
	else
		return (0);
}

long int	ft_convlong(const char *str, int i, int sign)
{
	long int res;

	res = 0;
	while (str[i] != '\0')
	{
		if (str[i] < 48 || str[i] > 57)
			break ;
		if (res >= 922337203685477580)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((long int)(res * sign));
}

long int	ft_atoilong(const char *str)
{
	int			i;
	long int	res;
	long int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (ft_convlong(str, i, sign));
}
