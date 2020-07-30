/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 17:10:56 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/30 17:17:08 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_params(t_data *data, int x)
{
	data->ray.camx = (2. * x / (double)data->resx) - 1;
	data->ray.raydirx = data->player.dirx + data->player.planex
		* data->ray.camx;
	data->ray.raydiry = data->player.diry + data->player.planey
		* data->ray.camx;
	data->ray.mapx = (int)data->player.posx;
	data->ray.mapy = (int)data->player.posy;
	data->ray.hit = 0;
	data->ray.deltadx = fabs(1. / data->ray.raydirx);
	data->ray.deltady = fabs(1. / data->ray.raydiry);
}

void		calc_sidedist(t_data *data)
{
	if (data->ray.raydirx < 0)
	{
		data->ray.stepx = -1;
		data->ray.sidedx = (data->player.posx - data->ray.mapx)
			* data->ray.deltadx;
	}
	else
	{
		data->ray.stepx = 1;
		data->ray.sidedx = (data->ray.mapx + 1.0 - data->player.posx)
			* data->ray.deltadx;
	}
	if (data->ray.raydiry < 0)
	{
		data->ray.stepy = -1;
		data->ray.sidedy = (data->player.posy - data->ray.mapy)
			* data->ray.deltady;
	}
	else
	{
		data->ray.stepy = 1;
		data->ray.sidedy = (data->ray.mapy + 1.0 - data->player.posy)
			* data->ray.deltady;
	}
}

void		dda_start(t_data *data)
{
	while (data->ray.hit == 0)
	{
		if (data->ray.sidedx < data->ray.sidedy)
		{
			data->ray.sidedx += data->ray.deltadx;
			data->ray.mapx += data->ray.stepx;
			data->ray.side = 0;
		}
		else
		{
			data->ray.sidedy += data->ray.deltady;
			data->ray.mapy += data->ray.stepy;
			data->ray.side = 1;
		}
		if (data->maparr[(int)data->ray.mapy][(int)data->ray.mapx] == '1')
			data->ray.hit = 1;
	}
}

int			dda_side(t_data *data)
{
	if (data->ray.side == 0)
	{
		data->ray.walldist = (data->ray.mapx - data->player.posx +
			(1. - data->ray.stepx) / 2.) / data->ray.raydirx;
		if (data->ray.mapx > data->player.posx)
			return (3);
		else
			return (1);
	}
	else
	{
		data->ray.walldist = (data->ray.mapy - data->player.posy +
			(1. - data->ray.stepy) / 2.) / data->ray.raydiry;
		if (data->ray.mapy > data->player.posy)
			return (0);
		else
			return (2);
	}
}

int			raycaster(t_data *data)
{
	int		x;
	double	textx;
	double	zbuffer[data->resx];

	x = 0;
	data->casts.zbuffer = zbuffer;
	while (x < data->resx)
	{
		init_params(data, x);
		calc_sidedist(data);
		dda_start(data);
		data->ray.compass = dda_side(data);
		textx = calc_drawline(data);
		drawer(data, x, textx);
		data->casts.zbuffer[x] = data->ray.walldist;
		x++;
	}
	sprite_order(data);
	sprite_render(data);
	if (data->save == 1)
		screenshotter(data);
	frame_update(data);
	return (0);
}
