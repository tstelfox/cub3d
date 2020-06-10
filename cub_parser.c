/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 11:56:20 by tmullan       #+#    #+#                 */
/*   Updated: 2020/06/10 15:04:46 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_res(char *lineread, t_data *mapdata, int i)
{
	while (!ft_isdigit(lineread[i]))
		i++;
	mapdata->resx = ft_atoi(&lineread[i]);
	while (ft_isdigit(lineread[i]))
		i++;
	mapdata->resy = ft_atoi(&lineread[i]);
	return (0);
}

int		get_floor(char *lineread, t_data *mapdata, int i)
{
	while (!ft_isdigit(lineread[i]))
		i++;
	mapdata->floor.t_rgb.r = ft_atoi(&lineread[i]);
	while (ft_isdigit(lineread[i]))
		i++;
	while (!ft_isdigit(lineread[i]))
		i++;
	mapdata->floor.t_rgb.g = ft_atoi(&lineread[i]);
	while (ft_isdigit(lineread[i]))
		i++;
	while (!ft_isdigit(lineread[i]))
		i++;
	mapdata->floor.t_rgb.b = ft_atoi(&lineread[i]);
	return (0);
}

int		get_ceiling(char *lineread, t_data *mapdata, int i)
{
	while (!ft_isdigit(lineread[i]))
		i++;
	mapdata->ceiling.t_rgb.r = ft_atoi(&lineread[i]);
	while (ft_isdigit(lineread[i]))
		i++;
	while (!ft_isdigit(lineread[i]))
		i++;
	mapdata->ceiling.t_rgb.g = ft_atoi(&lineread[i]);
	while (ft_isdigit(lineread[i]))
		i++;
	while (!ft_isdigit(lineread[i]))
		i++;
	mapdata->ceiling.t_rgb.b = ft_atoi(&lineread[i]);
	return (0);
}

int		get_map(char *lineread, t_data *mapdata)
{
	if (!mapdata->maptemp)
		mapdata->maptemp = ft_strdup(lineread);
	else
		mapdata->maptemp = ft_strjoinnl(mapdata->maptemp, lineread);
	return (0);
}

int		prs_wrld(t_data *mapdata, int argc, char *argv[])
{
	int		fd;
	int		i;
	char	*lineread;

	i = 0;
	if (argc == 1)
	{
		printf("Didn't attach a map file, bleedin eejit\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &lineread))
	{
		if (lineread[i] == 'R')
			i = get_res(lineread, mapdata, i);
		if (lineread[i] == 'F')
			i = get_floor(lineread, mapdata, i);
		if (lineread[i] == 'C')
			i = get_ceiling(lineread, mapdata, i);
		// if (lineread[i] == 'S')
		// 	;
		// if (lineread[i] == 'N' && lineread[i + 1] == 'O')
		// 	;
		// if (lineread[i] == 'E' && lineread[i + 1] == 'A')
		// 	;
		// if (lineread[i] == 'S' && lineread[i + 1] == 'O')
		// 	;
		// if (lineread[i] == 'W' && lineread[i + 1] == 'E')
		// 	;
		if (lineread[i] == '1')
			get_map(lineread, mapdata);
		free(lineread);
	}
	mapdata->maparr = ft_split(mapdata->maptemp, '\n');
	printf("Resolution is %d %d\n", mapdata->resx, mapdata->resy);
	printf("Floor colour is %X\n", mapdata->floor.colour);
	printf("Ceiling colour is %X\n", mapdata->ceiling.colour);
	free(mapdata->maptemp);
	printf("Let's try string number 1 of the array: %s\n", mapdata->maparr[0]);
	return (0);
}
