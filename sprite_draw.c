/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_draw.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 15:44:25 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/30 17:55:47 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		calc_sprite(t_data *data, int i)
{
	data->casts.spritex = data->sprite[i].x - data->player.posx;
	data->casts.spritey = data->sprite[i].y - data->player.posy;
	data->casts.invdet = 1.0 / (data->player.planex * data->player.diry -
		data->player.dirx * data->player.planey);
	data->casts.tranx = data->casts.invdet * (data->player.diry *
		data->casts.spritex - data->player.dirx * data->casts.spritey);
	data->casts.trany = data->casts.invdet * (-data->player.planey *
		data->casts.spritex + data->player.planex * data->casts.spritey);
	data->casts.screenx = (int)((data->resx / 2) *
		(1 + data->casts.tranx / data->casts.trany));
	data->casts.spriteh = abs((int)(data->resy / data->casts.trany));
	data->casts.dstarty = -data->casts.spriteh / 2 + data->resy / 2;
	if (data->casts.dstarty < 0)
		data->casts.dstarty = 0;
	data->casts.dendy = data->casts.spriteh / 2 + data->resy / 2;
	if (data->casts.dendy >= data->resy)
		data->casts.dendy = data->resy - 1;
	data->casts.spritew = abs((int)(data->resy / data->casts.trany));
	data->casts.dstartx = -data->casts.spritew / 2 + data->casts.screenx;
	if (data->casts.dstartx < 0)
		data->casts.dstartx = 0;
	data->casts.dendx = data->casts.spritew / 2 + data->casts.screenx;
	if (data->casts.dendx >= data->resx)
		data->casts.dendx = data->resx - 1;
}

void		sprite_draw(t_data *data, int x)
{
	int textx;
	int y;
	int d;
	int texy;

	textx = (int)(256 * (x - (-data->casts.spritew / 2 + data->casts.screenx))
			* data->spt.width / data->casts.spritew) / 256;
	y = data->casts.dstarty;
	if (data->casts.trany > 0 && x > 0 && x < data->resx &&
		data->casts.trany < data->casts.zbuffer[x])
	{
		while (y < data->casts.dendy)
		{
			d = (y) * 256 - data->resy * 128 + data->casts.spriteh * 128;
			texy = ((d * data->spt.height) / data->casts.spriteh) / 256;
			data->texcol.colour = colour_getter(data, textx, texy, 42);
			if (data->texcol.colour && data->texcol.t_rgb.a == 0)
				my_mlx_pixel_put(data, x, y, data->texcol.colour);
			y++;
		}
	}
}

void		sprite_render(t_data *data)
{
	int	i;
	int	x;

	i = 0;
	while (i < data->spritenum)
	{
		calc_sprite(data, i);
		x = data->casts.dstartx;
		while (x < data->casts.dendx)
		{
			sprite_draw(data, x);
			x++;
		}
		i++;
	}
}
