/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 17:10:56 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/15 17:58:24 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			raycaster(t_data *data)
{
	int x;

	x = 0;

	while (x < data->resx)
	{
		// Ray position and direction
		data->ray.camx = (2. * x / (double)data->resx) - 1;
		data->ray.raydirx = data->player.dirx + data->player.planex * data->ray.camx;
		data->ray.raydiry = data->player.diry + data->player.planey * data->ray.camx;
		data->ray.mapx = (int)data->player.posx;
		data->ray.mapy = (int)data->player.posy;
		data->ray.hit = 0;
		//Box of map
		//Length of ray from current pos to next x or y side
		//			sidedx & sidedy

		//Length of ray from x or y-side to next x or y side
		data->ray.deltadx = fabs(1. / data->ray.raydirx);
		data->ray.deltady = fabs(1. / data->ray.raydiry);
		//Direction to step in
		//			stepx & stepy

		//calculate step and initial sidedist
		if (data->ray.raydirx < 0)
		{
			data->ray.stepx = -1;
			data->ray.sidedx = (data->player.posx - data->ray.mapx) * data->ray.deltadx;
		}
		else
		{
			data->ray.stepx = 1;
			data->ray.sidedx = (data->ray.mapx + 1.0 - data->player.posx) * data->ray.deltadx;
		}
		if (data->ray.raydiry < 0)
		{
			data->ray.stepy = -1;
			data->ray.sidedy = (data->player.posy - data->ray.mapy) * data->ray.deltady;
		}
		else
		{
			data->ray.stepy = 1;
			data->ray.sidedy = (data->ray.mapy + 1.0 - data->player.posy) * data->ray.deltady;
		}
		//Perform DDA
		while (data->ray.hit == 0)
		{
			//Jump to next map square
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
			//Check if ray has hit wall
			if (data->maparr[(int)data->ray.mapy][(int)data->ray.mapx] == '1')
				data->ray.hit = 1;
		}
		//Calculate distance projected on camera direction
		int compass;
		if (data->ray.side == 0)
		{
			data->ray.walldist = (data->ray.mapx - data->player.posx + (1. - data->ray.stepx) / 2.) / data->ray.raydirx;
			if (data->ray.mapx > data->player.posx)
				compass = 3;
			else
				compass = 1;
		}
		else
		{
			data->ray.walldist = (data->ray.mapy - data->player.posy + (1. - data->ray.stepy) / 2.) / data->ray.raydiry;
			if (data->ray.mapy > data->player.posy)
				compass = 0;
			else
				compass = 2;
			
		}
		//Calculate height of line to draw
		data->ray.lineheight = (int)(data->resy / data->ray.walldist);
		//Calculate lowest and highest pixel
		data->ray.drawstart = -data->ray.lineheight / 2 + data->resy / 2;
		if (data->ray.drawstart < 0)
			data->ray.drawstart = 0;
		data->ray.drawend = data->ray.lineheight / 2 + data->resy / 2;
		if (data->ray.drawend >= data->resy)
			data->ray.drawend = data->resy - 1; // Taking out that 1 really fucks shit up
		// data->ray.drawend = data->resy - 1; Check later if not using this causes issues
		//ACtually drawing

		// int texnum = data->maparr[data->ray.mapy][data->ray.mapx] - 1; //Careful with char vs int here
		// printf("texnum be %d\n", texnum);
		// Calculate value of Wallx
		double wallx;
		if (data->ray.side == 0)
			wallx = data->player.posy + data->ray.walldist * data->ray.raydiry;
		else
			wallx = data->player.posx + data->ray.walldist * data->ray.raydirx;
		wallx -= floor(wallx);

		//x coordinate on the texture
		int textx = (int)(wallx * (double)(data->walls[0].width));
		if (data->ray.side == 0 && data->ray.raydirx > 0)
			textx = data->walls[0].width - textx - 1;
		if (data->ray.side == 1 && data->ray.raydiry < 0)
			textx = data->walls[0].width - textx - 1;

		double step = 1.0 * data->walls[0].height / data->ray.lineheight;

		double texpos = ((data->ray.drawstart - data->resy / 2 + data->ray.lineheight / 2) * step); //The - step is inexlicable

		unsigned int colour;
		int i = 0;
		while (i < data->ray.drawstart)
		{
			my_mlx_pixel_put(data, x, i, data->ceiling.colour);
			i++;
		}
		while (data->ray.drawstart <= data->ray.drawend)
		{
			colour = colour_getter(data, textx , texpos, compass);
			my_mlx_pixel_put(data, x, data->ray.drawstart, colour);
			texpos += step;
			data->ray.drawstart++;
		}
		i = data->ray.drawstart;
		while (i < data->resy)
		{
			my_mlx_pixel_put(data, x, i, data->floor.colour);
			i++;
		}
		x++;


		// mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win,
		// 	data->mlx.img, 0, 0);
		// printf("Walldist = [%f] || mapx,y [%d][%d] || stepx,y [%d][%d] || raydirx,y [%f][%f] || posx, y [%f][%f]\nDeltadx, y = [%f][%f] || sidedx, y [%f][%f]\n", data->ray.walldist,
		// 		data->ray.mapx, data->ray.mapy, data->ray.stepx, data->ray.stepy, data->ray.raydirx, data->ray.raydiry, data->player.posx, data->player.posy, data->ray.deltadx, data->ray.deltady, data->ray.sidedx, data->ray.sidedy);
	}
	movement(data);
	frame_update(data);
	return (0);
}
