/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_start.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 14:38:05 by tmullan       #+#    #+#                 */
/*   Updated: 2020/06/17 19:05:59 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		my_mlx_pixel_put(t_data *data, int x, int y, int colour)
{
	char	*dst;

	dst = data->mlx.addr + (y * data->mlx.linelen + x * (data->mlx.bpp / 8));
	*(unsigned int*)dst = colour;
}

void		raycaster(t_data *data)
{
	int x;

	x = 0;
	while (x < data->resx)
	{
		data->ray.camx = 2 * x / (double)data->resx - 1;
		data->ray.raydirx = data->player.dirx + data->player.planex * data->ray.camx;
		data->ray.raydiry = data->player.diry + data->player.planey * data->ray.camx;

		data->ray.mapx = (int)data->player.posx;
		data->ray.mapy = (int)data->player.posy;

		data->ray.deltadx = fabs(1 / data->ray.raydirx);
		data->ray.deltady = fabs(1 / data->ray.raydiry);

		if (data->ray.raydirx < 0)
		{
			data->ray.stepx = -1;
			data->ray.sidedx = (data->player.posx - data->ray.mapx) * data->ray.deltadx;
		}
		else
		{
			data->ray.stepx = 1;
			data->ray.sidedx = (data->ray.mapx + 1 - data->player.posx) * data->ray.deltadx;
		}
		if (data->ray.raydiry < 0)
		{
			data->ray.stepy = -1;
			data->ray.sidedy = (data->player.posy - data->ray.mapy) * data->ray.deltady;
		}
		else
		{
			data->ray.stepy = 1;
			data->ray.sidedy = (data->ray.mapy + 1 - data->player.posy) * data->ray.deltady;
		}
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
			if (data->maparr[data->ray.mapy][data->ray.mapx] > 0) //This line might be a culprit
				data->ray.hit = 1;
		}
		if (data->ray.side == 0)
			data->ray.walldist = (data->ray.mapx - data->player.posx + (1 - data->ray.stepx) / 2) / data->ray.raydirx;
		else
			data->ray.walldist = (data->ray.mapy - data->player.posy + (1 - data->ray.stepy) / 2) / data->ray.raydiry;
		data->ray.lineheight = (int)(data->resy / data->ray.walldist);
		data->ray.drawstart = -data->ray.lineheight / 2 + data->resy / 2;
		if (data->ray.drawstart < 0)
			data->ray.drawstart = 0;
		data->ray.drawend = data->ray.lineheight / 2 + data->resy / 2;
		if (data->ray.drawend >= data->resy)
			data->ray.drawend = data->resy - 1;
		// unsigned int colour = data->ceiling.colour;
		// if (data->ray.side == 1)
		// 	colour = colour / 2;
		int i = data->ray.drawstart;
		printf ("yar yar yar %d\n", data->ray.drawend);
		printf("Why why why %d\n", i);
		while (i < data->ray.drawend)
		{
			write(1, "1", 1);
			my_mlx_pixel_put(data, x, i, data->ceiling.colour);
			i++;
		}
		x++;
	}
}

void		mlx_start(t_data *data)
{
	// int x = 10;
	data->mlx.mlx = mlx_init();
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, data->resx,
			data->resy, "mumyer");

	data->mlx.img = mlx_new_image(data->mlx.mlx, data->resx, data->resy);

	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bpp,
			&data->mlx.linelen, &data->mlx.endian);

	raycaster(data);
	// while (x < 1000)
	// {
	// 	my_mlx_pixel_put(data, 10, x, data->ceiling.colour);
	// 	x++;
	// }
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win,
			data->mlx.img, 0, 0);
	mlx_loop(data->mlx.mlx);
}
