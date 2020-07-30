/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawline.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/30 16:51:30 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/30 17:23:18 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			calc_drawline(t_data *data)
{
	double wallx;
	double textx;

	data->ray.lineheight = (int)(data->resy / data->ray.walldist);
	data->ray.drawstart = -data->ray.lineheight / 2 + data->resy / 2;
	if (data->ray.drawstart < 0)
		data->ray.drawstart = 0;
	data->ray.drawend = data->ray.lineheight / 2 + data->resy / 2;
	if (data->ray.drawend >= data->resy)
		data->ray.drawend = data->resy - 1;
	if (data->ray.side == 0)
		wallx = data->player.posy + data->ray.walldist * data->ray.raydiry;
	else
		wallx = data->player.posx + data->ray.walldist * data->ray.raydirx;
	wallx -= floor(wallx);
	textx = (int)(wallx * (double)(data->walls[data->ray.compass].width));
	if (data->ray.side == 0 && data->ray.raydirx > 0)
		textx = data->walls[data->ray.compass].width - textx - 1;
	if (data->ray.side == 1 && data->ray.raydiry < 0)
		textx = data->walls[data->ray.compass].width - textx - 1;
	return (textx);
}

void		drawing(t_data *data, int x, double texpos, double textx)
{
	int		i;
	int		texy;
	double	colour;

	i = 0;
	while (i < data->ray.drawstart)
	{
		my_mlx_pixel_put(data, x, i, data->ceiling.colour);
		i++;
	}
	while (i <= data->ray.drawend)
	{
		texy = (int)texpos & (data->walls[data->ray.compass].height - 1);
		colour = colour_getter(data, textx, texy, data->ray.compass);
		texpos += data->ray.step;
		my_mlx_pixel_put(data, x, i, colour);
		i++;
	}
	while (i < data->resy)
	{
		my_mlx_pixel_put(data, x, i, data->floor.colour);
		i++;
	}
}

void		drawer(t_data *data, int x, double textx)
{
	double	texpos;
	int		i;

	data->ray.step = 1.0 * data->walls[data->ray.compass].height
		/ data->ray.lineheight;
	texpos = ((data->ray.drawstart - data->resy / 2 +
		data->ray.lineheight / 2) * data->ray.step);
	i = 0;
	drawing(data, x, texpos, textx);
}
