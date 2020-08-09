/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 16:41:28 by tmullan       #+#    #+#                 */
/*   Updated: 2020/08/09 20:06:20 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		get_map(char *line, t_data *data)
{
	if (!data->maptemp && !ft_isalpha(line[0]))
		data->maptemp = ft_strdup(line);
	else
		data->maptemp = ft_strjoinnl(data->maptemp, line, 0, 0);
}

int			findchar(char c, char *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

void		flood_fill(t_data *data, int y, int x, char **floodmap)
{
	if ((y + 1) == data->maplength || floodmap[y + 1][0] == '\n' ||
			floodmap[y + 1][0] == '\0' || floodmap[y][x] == ' '
			|| floodmap[y][x] == '\0' || y == 0
			|| floodmap[y][x] == '\n' || floodmap[y][x + 1] == '\0' || x == 0
			|| floodmap[y + 1][x] == '\0' || floodmap[y][0] == '\n')
		bad_input(ERR_MAP);
	if (floodmap[y][x] == '0' || floodmap[y][x] == '2')
		floodmap[y][x] = 'f';
	if (findchar(floodmap[y - 1][x], "02 \0"))
		flood_fill(data, y - 1, x, floodmap);
	if (findchar(floodmap[y][x + 1], "02 \0"))
		flood_fill(data, y, x + 1, floodmap);
	if (findchar(floodmap[y + 1][x], "02 \0"))
		flood_fill(data, y + 1, x, floodmap);
	if (findchar(floodmap[y][x - 1], "02 \0"))
		flood_fill(data, y, x - 1, floodmap);
	if (findchar(floodmap[y - 1][x + 1], "02 \0"))
		flood_fill(data, y - 1, x + 1, floodmap);
	if (findchar(floodmap[y - 1][x - 1], "02 \0"))
		flood_fill(data, y - 1, x - 1, floodmap);
	if (findchar(floodmap[y + 1][x + 1], "02 \0"))
		flood_fill(data, y + 1, x + 1, floodmap);
	if (findchar(floodmap[y + 1][x - 1], "02 \0"))
		flood_fill(data, y + 1, x - 1, floodmap);
}

void		make_floodmap(t_data *data, char **floodmap)
{
	int i;

	i = 0;
	while (data->maparr[i])
		i++;
	data->maplength = i;
	floodmap = (char **)malloc(sizeof(char *) * i);
	if (floodmap == 0)
		bad_input("Error\nMalloc failed\n");
	i = 0;
	while (data->maparr[i])
	{
		floodmap[i] = ft_strdup(data->maparr[i]);
		i++;
	}
	flood_fill(data, data->player.posy, data->player.posx, floodmap);
	i = 0;
	while (i < data->maplength)
	{
		free(floodmap[i]);
		i++;
	}
	free(floodmap);
}

void		map_check(t_data *data)
{
	int		i;
	int		flag;
	char	**floodmap;

	i = 0;
	flag = 0;
	floodmap = NULL;
	while (ft_whitespace(data->maptemp[i]))
		i++;
	while (data->maptemp[i])
	{
		if (ft_isalpha(data->maptemp[i]))
			flag = 1;
		i++;
		if (ft_isalpha(data->maptemp[i]) && flag == 1)
			bad_input(ERR_MAP);
	}
	if (flag == 0)
		bad_input(ERR_MAP);
	player(data);
	make_floodmap(data, floodmap);
}
