/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 12:44:10 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/08 17:42:19 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		mfailexit(int ret, char **line)
{
	if (ret == -1)
	{
		free(*line);
		return (-1);
	}
	else
		return (1);
}

int		newline(char *buff)
{
	int i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

int		processbuff(char *buff, char **line)
{
	int len;

	len = newline(buff);
	if (!*line)
		*line = ft_strdup1(buff);
	else
		*line = ft_strjoin1(*line, buff);
	if (*line == NULL)
		return (-1);
	if (buff[0] == '\n')
	{
		ft_memmove1(buff, buff + 1, ft_strlen(buff));
		return (1);
	}
	if (!newline(buff))
		return (0);
	else
	{
		ft_memmove1(buff, buff + (len + 1), ft_strlen(buff));
		return (1);
	}
}

int		remaining(char *buff, char **line)
{
	if (buff[0] == '\n')
	{
		*line = ft_strdup1("");
		ft_memmove1(buff, buff + 1, ft_strlen(buff));
		return (*line == 0 ? -1 : 1);
	}
	if (newline(buff))
	{
		if (!*line)
		{
			*line = ft_strdup1(buff);
			ft_memmove1(buff, buff + (newline(buff) + 1),
			ft_strlen(buff));
			return (*line == 0 ? -1 : 1);
		}
		else
		{
			*line = ft_strjoin1(*line, buff);
			return (*line == 0 ? -1 : 1);
		}
	}
	else
		*line = ft_strdup1(buff);
	return (*line == 0 ? -1 : 0);
}

int		get_next_line(int fd, char **line)
{
	static char	buff[FD_MAX][BUFFER_SIZE + 1];
	int			res;
	int			ret;

	*line = NULL;
	res = 1;
	if (*buff[fd] != '\0')
	{
		ret = remaining(buff[fd], line);
		if (ret != 0)
			return (mfailexit(ret, line));
	}
	while (res)
	{
		res = read(fd, buff[fd], BUFFER_SIZE);
		if (res == -1 || fd < 0)
			return (-1);
		buff[fd][res] = '\0';
		ret = processbuff(buff[fd], line);
		if (ret != 0)
			return (mfailexit(ret, line));
	}
	return (0);
}
