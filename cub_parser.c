/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 11:56:20 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/14 14:27:03 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_res(char *lineread, t_data *data, int i)
{
	while (!ft_isdigit(lineread[i]))
		i++;
	data->resx = ft_atoi(&lineread[i]);
	while (ft_isdigit(lineread[i]))
		i++;
	data->resy = ft_atoi(&lineread[i]);
	return (0);
}

int		get_floor(char *lineread, t_data *data, int i)
{
	while (!ft_isdigit(lineread[i]))
		i++;
	data->floor.t_rgb.r = ft_atoi(&lineread[i]);
	while (ft_isdigit(lineread[i]))
		i++;
	while (!ft_isdigit(lineread[i]))
		i++;
	data->floor.t_rgb.g = ft_atoi(&lineread[i]);
	while (ft_isdigit(lineread[i]))
		i++;
	while (!ft_isdigit(lineread[i]))
		i++;
	data->floor.t_rgb.b = ft_atoi(&lineread[i]);
	return (0);
}

int		get_ceiling(char *lineread, t_data *data, int i)
{
	while (!ft_isdigit(lineread[i]))
		i++;
	data->ceiling.t_rgb.r = ft_atoi(&lineread[i]);
	while (ft_isdigit(lineread[i]))
		i++;
	while (!ft_isdigit(lineread[i]))
		i++;
	data->ceiling.t_rgb.g = ft_atoi(&lineread[i]);
	while (ft_isdigit(lineread[i]))
		i++;
	while (!ft_isdigit(lineread[i]))
		i++;
	data->ceiling.t_rgb.b = ft_atoi(&lineread[i]);
	return (0);
}

int		get_n_texture(char *lineread, t_data *data, int i)
{
	while (lineread[i] != '.')
		i++;
	data->tex[0] = ft_strdup(&lineread[i]);
	return (0);
}

int		get_map(char *lineread, t_data *data)
{
	if (!data->maptemp)
		data->maptemp = ft_strdup(lineread);
	else
		data->maptemp = ft_strjoinnl(data->maptemp, lineread);
	return (0);
}

void	west_dir(t_data *data)
{
	data->player.dirx = -1;
	data->player.diry = 0;
	data->player.planex = 0;
	data->player.planey = -0.66;
}

void	east_dir(t_data *data)
{
	data->player.dirx = 1;
	data->player.diry = 0;
	data->player.planex = 0;
	data->player.planey = 0.66;
}

void	north_dir(t_data *data)
{
	data->player.dirx = 0;
	data->player.diry = -1;
	data->player.planey = 0;
	data->player.planex = 0.66;
}

void	south_dir(t_data *data)
{
	data->player.dirx = 0;
	data->player.diry = 1;
	data->player.planey = 0;
	data->player.planex = -0.66;
}

void	player_pos(t_data *data, int i, int k)
{
	data->player.posx = (double)(k + 0.5);
	data->player.posy = (double)(i + 0.5);
	if (data->maparr[i][k] == 'E')
		east_dir(data);
	if (data->maparr[i][k] == 'N')
		north_dir(data);
	if (data->maparr[i][k] == 'W')
		west_dir(data);
	if (data->maparr[i][k] == 'S')
		south_dir(data);
}

void	player(t_data *data)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	while (data->maparr[i][k])
	{
		// printf("The full line is: %s\n", data->maparr[i]);
		if (ft_isalpha(data->maparr[i][k]))
		{
			// printf("x and y are : %d %d\n", k, i);
			// printf("The element is: %c\n", data->maparr[i][k]);
			player_pos(data, i, k);
			break ;
		}
		k++;
		if (!data->maparr[i][k])
		{
			k = 0;
			i++;
		}
	}
}


int		prs_wrld(t_data *data, int argc, char *argv[])
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
			i = get_res(lineread, data, i);
		if (lineread[i] == 'F')
			i = get_floor(lineread, data, i);
		if (lineread[i] == 'C')
			i = get_ceiling(lineread, data, i);
		if (lineread[i] == 'N' && lineread[i + 1] == 'O')
			i = get_n_texture(lineread, data, i);
		// if (lineread[i] == 'S')
		// 	;
		// if (lineread[i] == 'E' && lineread[i + 1] == 'A')
		// 	;
		// if (lineread[i] == 'S' && lineread[i + 1] == 'O')
		// 	;
		// if (lineread[i] == 'W' && lineread[i + 1] == 'E')
		// 	;
		if (lineread[i] == '1')
			get_map(lineread, data);
		free(lineread);
	}
	data->maparr = ft_split(data->maptemp, '\n');
	player(data);
	free(data->maptemp);
	return (0);
}

	// printf("Let's try string number 1 of the array: %s\n", data->maparr[3]);
	// printf("Resolution is %d %d\n", data->resx, data->resy);
	// printf("Floor colour is %X\n", data->floor.colour);
	// printf("Ceiling colour is %X\n", data->ceiling.colour);