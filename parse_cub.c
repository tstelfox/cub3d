/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cub.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/13 11:59:35 by tmullan       #+#    #+#                 */
/*   Updated: 2020/05/16 11:58:25 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	data_init(t_data *mapdata)
{
	mapdata->resx = 0;
	mapdata->resy = 0;
	// mapdata->floor.t_rgb = 0;
}

int		prs_wrld(t_data *mapdata, int argc, char *argv[])
{
	int		fd;
	int		i;
	char	*lineread;

	i = 0;
	// Need to build framework to verify if input is valid
	if (argc == 1)
	{
		printf("Didn't attach a map file, bleedin eejit\n");
		return (1);
	}
	// if (argc > 2) This is for the --save part
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &lineread))
	{
		if (lineread[i] == 'R') //Resolution
		{
			while (!ft_isdigit(lineread[i]))
				i++;
			mapdata->resx = ft_atoi(&lineread[i]);
			while (ft_isdigit(lineread[i]))
				i++;
			mapdata->resy = ft_atoi(&lineread[i]);
			i = 0;
		}
		// if lineread is NO/EA/SO/WE/S
		if (lineread[i] == 'F') //Floor colour
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
			i = 0;
		}
		if (lineread[i] =='C') //Ceiling colour
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
			i = 420;
		}
		if (i == 420)
		{
			// Here the hard part. Working out if the map is valid.
			// Also how do I store this shit?
		}
		// if there are more than three 1s in succession
		free(lineread);
		// printf("%s\n", lineread);
	}
	printf("%d\n", mapdata->resx);
	printf("%d\n", mapdata->resy);
	printf("%d\n", mapdata->floor.t_rgb.r);
	printf("%d\n", mapdata->floor.t_rgb.g);
	printf("%d\n", mapdata->floor.t_rgb.b);
	printf("%d\n", mapdata->ceiling.t_rgb.r);
	printf("%d\n", mapdata->ceiling.t_rgb.g);
	printf("%d\n", mapdata->ceiling.t_rgb.b);

	return (0);
}
