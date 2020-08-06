/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 16:41:28 by tmullan       #+#    #+#                 */
/*   Updated: 2020/08/06 16:45:37 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	// printf("Let's see where we're going x and y %d %d\n", x, y);
	// printf("This mapspace is %c\n", floodmap[y][x]);
	if (floodmap[y][x] == ' ' || floodmap[y][x] == '\0'
			|| floodmap[y][x] == '\n' || !floodmap[y][x]
			|| floodmap[y][x + 1] == '\0' || x == 0
			|| (y + 1) == data->maplength || y == 0)
		bad_input(data, ERR_MAP);
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

void		map_check(t_data *data)
{
	int		i;
	int		flag;
	char	**floodmap;

	i = 0;
	flag = 0;
	while (data->maptemp[i])
	{
		if (ft_isalpha(data->maptemp[i]))
			flag = 1;
		i++;
		if (ft_isalpha(data->maptemp[i]) && flag == 1)
			bad_input(data, ERR_MAP);
	}
	if (flag == 0)
		bad_input(data, ERR_MAP);
	player(data);
	i = 0;
	while (data->maparr[i])
		i++;
	data->maplength = i;
	floodmap = (char **)malloc(sizeof(char *) * i);
	i = 0;
	while (data->maparr[i])
	{
		floodmap[i] = ft_strdup(data->maparr[i]);
		// printf("%s\n", floodmap[i]);
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
	// i = 0;
	// while (i < data->maplength)
	// {
	// 	printf("%s\n", floodmap[i]);
	// 	i++;
	// }
}
