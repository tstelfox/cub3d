/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 11:56:20 by tmullan       #+#    #+#                 */
/*   Updated: 2020/08/06 19:00:18 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		get_res(char *line, t_data *data, int i)
{
	int x;
	int y;

	while (!ft_isdigit(line[i]))
		!ft_whitespace(line[i]) ? bad_input(ERR_RES) : i++;
	data->resx = ft_atoilong(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	data->resy = ft_atoilong(&line[i]);
	while (ft_isdigit(line[i]) || ft_whitespace(line[i]))
		i++;
	while (line[i] != '\0')
		!ft_whitespace(line[i]) ? bad_input(ERR_RES) : i++;
	if (data->resx <= 0 || data->resy <= 0)
		bad_input(ERR_RES);
	if (data->save == 1)
		return ;
	mlx_get_screen_size(data->mlx.mlx, &x, &y);
	if (data->resx > x)
		data->resx = x;
	if (data->resy > y)
		data->resy = y;
}

void		get_floor(char *line, t_data *data, int i)
{
	int temp;

	temp = 0;
	while (ft_whitespace(line[i]))
		i++;
	ft_isdigit(line[i]) ? temp = ft_atoilong(&line[i]) : bad_input(ERR_F);
	temp <= 255 && temp >= 0 ? data->floor.t_rgb.r = temp
			: bad_input(ERR_F);
	while (ft_isdigit(line[i]))
		i++;
	line[i] != ',' ? bad_input(ERR_F) : i++;
	ft_isdigit(line[i]) ? temp = ft_atoilong(&line[i]) :
			bad_input(ERR_F);
	temp <= 255 && temp >= 0 ? data->floor.t_rgb.g = temp :
			bad_input(ERR_F);
	while (ft_isdigit(line[i]))
		i++;
	line[i] != ',' ? bad_input(ERR_F) : i++;
	temp = ft_atoilong(&line[i]);
	temp <= 255 && temp >= 0 ? data->floor.t_rgb.b = temp :
			bad_input(ERR_F);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] != '\0')
		ft_whitespace(line[i]) ? i++ : bad_input(ERR_F);
}

void		get_ceiling(char *line, t_data *data, int i)
{
	int temp;

	temp = 0;
	while (ft_whitespace(line[i]))
		i++;
	ft_isdigit(line[i]) ? temp = ft_atoilong(&line[i]) : bad_input(ERR_C);
	temp <= 255 && temp >= 0 ? data->ceiling.t_rgb.r = temp
			: bad_input(ERR_C);
	while (ft_isdigit(line[i]))
		i++;
	line[i] != ',' ? bad_input(ERR_C) : i++;
	ft_isdigit(line[i]) ? temp = ft_atoilong(&line[i]) : bad_input(ERR_C);
	temp <= 255 && temp >= 0 ? data->ceiling.t_rgb.g = temp :
			bad_input(ERR_C);
	while (ft_isdigit(line[i]))
		i++;
	line[i] != ',' ? bad_input(ERR_C) : i++;
	temp = ft_atoilong(&line[i]);
	temp <= 255 && temp >= 0 ? data->ceiling.t_rgb.b = temp :
			bad_input(ERR_C);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] != '\0')
		ft_whitespace(line[i]) ? i++ : bad_input(ERR_C);
}

void		get_sprite(char *line, t_data *data, int i)
{
	int fd;

	while (ft_whitespace(line[i]))
		i++;
	data->sprite_addr = ft_strdup(&line[i]);
	if (ft_strcmp(&data->sprite_addr[ft_strlen(data->sprite_addr) - 4], ".xpm"))
		bad_input("Error\nTextures must be in .xpm format\n");
	fd = open(data->sprite_addr, O_RDONLY);
	if (fd == -1)
		bad_input("Error\nSprite texture damaged or missing\n");
	close(fd);
}

void		get_texture(char *line, t_data *data, int i, int side)
{
	int fd;

	while (ft_whitespace(line[i]))
		i++;
	data->tex[side] = ft_strdup(&line[i]);
	if (ft_strcmp(&data->tex[side][ft_strlen(data->tex[side]) - 4], ".xpm"))
		bad_input("Error\nTextures must be in .xpm format\n");
	fd = open(data->tex[side], O_RDONLY);
	if (fd == -1)
		bad_input("Error\nWall texture damaged or missing\n");
	close(fd);
}

void		get_map(char *line, t_data *data)
{
	if (!data->maptemp && !ft_isalpha(line[0]))
		data->maptemp = ft_strdup(line);
	else
		data->maptemp = ft_strjoinnl(data->maptemp, line, 0, 0);
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
	int		i;
	int		k;
	char	p;

	i = 1;
	k = 0;
	while (data->maparr[i][k])
	{
		if (ft_isalpha(data->maparr[i][k]))
		{
			p = data->maparr[i][k];
			if (p != 'N' && p != 'S' && p != 'W' && p != 'E')
				bad_input(ERR_MAP);
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

void		get_configs(t_data *data, char *line, int i)
{
	if (line[i] == 'R')
		get_res(line, data, i + 1);
	if (line[i] == 'F')
		get_floor(line, data, i + 1);
	if (line[i] == 'C')
		get_ceiling(line, data, i + 1);
	if (line[i] == 'N' && line[i + 1] == 'O')
		get_texture(line, data, i + 2, 0);
	if (line[i] == 'E' && line[i + 1] == 'A')
		get_texture(line, data, i + 2, 1);
	if (line[i] == 'S' && line[i + 1] == 'O')
		get_texture(line, data, i + 2, 2);
	if (line[i] == 'W' && line[i + 1] == 'E')
		get_texture(line, data, i + 2, 3);
	if (line[i] == 'S' && line[i + 1] != 'O')
		get_sprite(line, data, i + 1);
	if (data->parse[8] == 1)
		get_map(line, data);
	free(line);
	line = NULL;
}

int			elem_check(t_data *data, int i)
{
	while (i < 8)
	{
		if (data->parse[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

void		count_configs(t_data *data, char *line, int i)
{
	if (line[i] == 'R')
		data->parse[0] == 0 ? data->parse[0] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'F')
		data->parse[1] == 0 ? data->parse[1] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'C')
		data->parse[2] == 0 ? data->parse[2] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'N' && line[i + 1] == 'O')
		data->parse[3] == 0 ? data->parse[3] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'E' && line[i + 1] == 'A')
		data->parse[4] == 0 ? data->parse[4] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'S' && line[i + 1] == 'O')
		data->parse[5] == 0 ? data->parse[5] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'W' && line[i + 1] == 'E')
		data->parse[6] == 0 ? data->parse[6] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'S' && line[i + 1] != 'O')
		data->parse[7] == 0 ? data->parse[7] = 1 : bad_input(ERR_ELEM);
	if (!ft_whitespace(line[i]) && line[i] != 'R' && line[i] != 'F'
			&& line[i] != 'C' && line[i] != 'N' && line[i] != 'E' &&
			line[i] != 'S' && line[i] != 'W' && line[i] != '\n'
			&& line[i] != '1' && line[i] != '\0' && line[i] != '0')
		bad_input("Error\nUnknown element\n");
	if (elem_check(data, i))
		data->parse[8] = 1;
}

int			prs_wrld(t_data *data, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (get_next_line(fd, &line))
	{
		count_configs(data, line, i);
		get_configs(data, line, i);
	}
	count_configs(data, line, i);
	get_configs(data, line, i);
	if (data->parse[8] == 0)
		bad_input(ERR_ELEM);
	if (data->maptemp == NULL)
		bad_input(ERR_MAP);
	data->maparr = ft_split_extra(data->maptemp, '\n');
	// printf("What %s\n", data->maptemp);
	map_check(data);
	sprites_init(data);
	// player(data);
	// if (line != NULL)
	// 	free(line);
	free(data->maptemp);
	return (0);
}
