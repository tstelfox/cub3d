/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 11:56:20 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/29 16:22:39 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		get_res(char *lineread, t_data *data, int i)
{
	int x;
	int y;

	while (!ft_isdigit(lineread[i]))
		!ft_whitespace(lineread[i]) ? bad_input(data, ERR_RES) : i++;
	data->resx = ft_atoi(&lineread[i]);
	while (ft_isdigit(lineread[i]))
		i++;
	data->resy = ft_atoi(&lineread[i]);
	while (ft_isdigit(lineread[i]) || ft_whitespace(lineread[i]))
		i++;
	while (lineread[i] != '\0')
		!ft_whitespace(lineread[i]) ? bad_input(data, ERR_RES) : i++;
	if (data->resx <= 0 || data->resy <= 0)
		bad_input(data, ERR_RES);
	if (data->save == 1)
		return ;
	mlx_get_screen_size(data->mlx.mlx, &x, &y);
	if (data->resx > x)
		data->resx = x;
	if (data->resy > y)
		data->resy = y;
}

void		get_floor(char *lineread, t_data *data, int i)
{
	int temp;
	
	while (ft_whitespace(lineread[i]))
		i++;
	ft_isdigit(lineread[i]) ? temp = ft_atoi(&lineread[i]) :
			bad_input(data, ERR_FLOOR);
	temp <= 255 && temp >= 0 ? data->floor.t_rgb.r = temp
			: bad_input(data, ERR_FLOOR);
	while (ft_isdigit(lineread[i]))
		i++;
	lineread[i] != ',' ? bad_input(data, ERR_FLOOR) : i++;
	ft_isdigit(lineread[i]) ? temp = ft_atoi(&lineread[i]) :
			bad_input(data, ERR_FLOOR);
	temp <= 255 && temp >= 0 ? data->floor.t_rgb.g = temp :
			bad_input(data, ERR_FLOOR);
	while (ft_isdigit(lineread[i]))
		i++;
	lineread[i] != ',' ? bad_input(data, ERR_FLOOR) : i++;
	temp = ft_atoi(&lineread[i]);
	temp <= 255 && temp >= 0 ? data->floor.t_rgb.b = temp :
			bad_input(data, ERR_FLOOR);
	while (ft_isdigit(lineread[i]))
		i++;
	while (lineread[i] != '\0')
		ft_whitespace(lineread[i]) ? i++ : bad_input(data, ERR_FLOOR);
}

void		get_ceiling(char *lineread, t_data *data, int i)
{
	int temp;
	
	while (ft_whitespace(lineread[i]))
		i++;
	ft_isdigit(lineread[i]) ? temp = ft_atoi(&lineread[i]) :
			bad_input(data, ERR_CEILING);
	temp <= 255 && temp >= 0 ? data->ceiling.t_rgb.r = temp
			: bad_input(data, ERR_CEILING);
	while (ft_isdigit(lineread[i]))
		i++;
	lineread[i] != ',' ? bad_input(data, ERR_CEILING) : i++;
	ft_isdigit(lineread[i]) ? temp = ft_atoi(&lineread[i]) :
			bad_input(data, ERR_CEILING);
	temp <= 255 && temp >= 0 ? data->ceiling.t_rgb.g = temp :
			bad_input(data, ERR_CEILING);
	while (ft_isdigit(lineread[i]))
		i++;
	lineread[i] != ',' ? bad_input(data, ERR_CEILING) : i++;
	temp = ft_atoi(&lineread[i]);
	temp <= 255 && temp >= 0 ? data->ceiling.t_rgb.b = temp :
			bad_input(data, ERR_CEILING);
	while (ft_isdigit(lineread[i]))
		i++;
	while (lineread[i] != '\0')
		ft_whitespace(lineread[i]) ? i++ : bad_input(data, ERR_CEILING);
}

void	get_sprite(char *lineread, t_data *data, int i)
{
	while (lineread[i] != '.')
		i++;
	data->sprite_addr = ft_strdup(&lineread[i]);
}

void		get_texture(char *lineread, t_data *data, int i, int side)
{
	while (lineread[i] != '.')
		i++;
	data->tex[side] = ft_strdup(&lineread[i]);
}

void		get_map(char *lineread, t_data *data)
{
	if (!data->maptemp)
		data->maptemp = ft_strdup(lineread);
	else
		data->maptemp = ft_strjoinnl(data->maptemp, lineread);
}

void		west_dir(t_data *data)
{
	data->player.dirx = -1;
	data->player.diry = 0;
	data->player.planex = 0;
	data->player.planey = -0.66;
}

void		east_dir(t_data *data)
{
	data->player.dirx = 1;
	data->player.diry = 0;
	data->player.planex = 0;
	data->player.planey = 0.66;
}

void		north_dir(t_data *data)
{
	data->player.dirx = 0;
	data->player.diry = -1;
	data->player.planey = 0;
	data->player.planex = 0.66;
}

void		south_dir(t_data *data)
{
	data->player.dirx = 0;
	data->player.diry = 1;
	data->player.planey = 0;
	data->player.planex = -0.66;
}

void		player_pos(t_data *data, int i, int k)
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

void		player(t_data *data)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	while (data->maparr[i][k])
	{
		if (ft_isalpha(data->maparr[i][k]))
		{
			player_pos(data, i, k);
			data->maparr[i][k] = '0';
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

int			prs_wrld(t_data *data, int argc, char *argv[])
{
	int		fd;
	int		i;
	char	*lineread;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &lineread))
	{
		if (lineread[i] == 'R')
			get_res(lineread, data, i + 1);
		if (lineread[i] == 'F')
			get_floor(lineread, data, i + 1);
		if (lineread[i] == 'C')
			get_ceiling(lineread, data, i + 1);
		if (lineread[i] == 'N' && lineread[i + 1] == 'O')
			get_texture(lineread, data, i, 0);
		if (lineread[i] == 'E' && lineread[i + 1] == 'A')
			get_texture(lineread, data, i, 1);
		if (lineread[i] == 'S' && lineread[i + 1] == 'O')
			get_texture(lineread, data, i, 2);
		if (lineread[i] == 'W' && lineread[i + 1] == 'E')
			get_texture(lineread, data, i, 3);
		if (lineread[i] == 'S' && lineread[i + 1] != 'O')
			get_sprite(lineread, data, i);
		if (lineread[i] == '1')
			get_map(lineread, data);
		i = 0;
		free(lineread);
	}
	data->maparr = ft_split(data->maptemp, '\n');
	sprites_init(data);
	// printf("Number of sprites do be: %d\n", data->spritenum);
	player(data);
	free(data->maptemp);
	close(fd);
	return (0);
}
