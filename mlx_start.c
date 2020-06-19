/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_start.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 14:38:05 by tmullan       #+#    #+#                 */
/*   Updated: 2020/06/19 18:54:05 by tmullan       ########   odam.nl         */
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
	data->ray.mapx = (int)data->player.posx;
	data->ray.mapy = (int)data->player.posy;
	while (x < data->resx)
	{
		// Ray position and direction
		data->ray.camx = (2 * x / (double)data->resx) - 1;
		data->ray.raydirx = data->player.dirx + data->player.planex * data->ray.camx;
		data->ray.raydiry = data->player.diry + data->player.planey * data->ray.camx;
		//Box of map
		// printf("what is mapx: %f\n", data->ray.mapx);
		// printf("what is mapy: %f\n", data->ray.mapy);
		// return ;
		//Length of ray from current pos to next x or y side
		//			sidedx & sidedy

		//Length of ray from x or y-side to next x or y side
		data->ray.deltadx = fabs(1.0 / data->ray.raydirx);
		data->ray.deltady = fabs(1.0 / data->ray.raydiry);
		// printf("what is deltax: %f\n", data->ray.deltadx);
		// printf("what is deltay: %f\n", data->ray.deltady);
		// return ;
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
				// printf("stepx is: %d\n", data->ray.stepx);
				// printf("Where we actually end up: %f %f\n", data->ray.mapx, data->ray.mapy);
			}
			else
			{
				data->ray.sidedy += data->ray.deltady;
				data->ray.mapy += data->ray.stepy;
				data->ray.side = 1;
			}
			//Check if ray has hit wall
			if (data->maparr[(int)data->ray.mapy][(int)data->ray.mapx] == '1') //I think it isn't checking the map properly. Only checking the first row
				data->ray.hit = 1;
		}
	//Calculate distance projected on camera direction
		if (data->ray.side == 0)
			data->ray.walldist = (data->ray.mapx - data->player.posx + (1.0 - data->ray.stepx) / 2.0) / data->ray.raydirx;
		else
		{
			data->ray.walldist = (data->ray.mapy - data->player.posy + (1.0 - data->ray.stepy) / 2.0) / data->ray.raydiry;
		}
		// printf("wall distance %f = (data->ray.mapy [%d]- data->player.posy [%f]+ (1 - data->ray.stepy)[%d] / 2) / data->ray.raydiry[%f]\n", data->ray.walldist, data->ray.mapy, data->player.posy, data->ray.stepy, data->ray.raydiry);
		printf("Walldist = [%f] || mapx,y [%f][%f] || stepx,y [%d][%d] || raydirx,y [%f][%f]\n", data->ray.walldist, data->ray.mapx, data->ray.mapy, data->ray.stepx, data->ray.stepy, data->ray.raydirx, data->ray.raydiry);
		// return ;
		//Calculate height of line to draw
		data->ray.lineheight = (int)(data->resy / data->ray.walldist);
		//Calculate lowest and highest pixel
		data->ray.drawstart = -data->ray.lineheight / 2 + data->resy / 2;
		if (data->ray.drawstart < 0)
			data->ray.drawstart = 0;
		data->ray.drawend = data->ray.lineheight / 2 + data->resy / 2;
		if (data->ray.drawend >= data->resy)
			data->ray.drawend = data->resy - 1;
		// printf("Why why why drawstart %d\n", data->ray.drawstart);
		// printf ("yar yar yar drawend%d\n", data->ray.drawend);
		// return ;
		// printf("lineheight do be: %d\n", data->ray.lineheight);
		// c
		// printf("What is walldist: %f\n", data->ray.walldist);
		// return ;
		//ACtually drawing
		while (data->ray.drawstart <= data->ray.drawend)
		{
			my_mlx_pixel_put(data, x, data->ray.drawstart, data->ceiling.colour);
			data->ray.drawstart++;
		}
		printf("Why why why drawstart %d\n", data->ray.drawstart);
		printf ("yar yar yar drawend%d\n", data->ray.drawend);
		// return ;
		printf("lineheight do be: %d\n", data->ray.lineheight);
		// printf("Where we actually end up: %d %d\n", data->ray.mapx, data->ray.mapy);
		x++;
	}
	// printf("x arrives at: %d\n", x);
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








// Just don't go down here





// void		raycaster(t_data *data)
// {
// 	int x;

// 	x = 0;
// 	while (x < data->resx)
// 	{
// 		data->ray.camx = 2 * x / (double)data->resx - 1;
// 		data->ray.raydirx = data->player.dirx + data->player.planex * data->ray.camx;
// 		data->ray.raydiry = data->player.diry + data->player.planey * data->ray.camx;
// 		// printf("the raydiry here be: %f\n", data->ray.raydiry);
// 		// printf("the raydirx here be: %f\n", data->ray.raydirx);
// 		// printf("Camx is: %f\n", data->ray.camx);
// 		// return ;


// 		data->ray.mapx = int(data->player.posx);
// 		data->ray.mapy = int(data->player.posy);

// 		data->ray.deltadx = fabs(1 / data->ray.raydirx);
// 		data->ray.deltady = fabs(1 / data->ray.raydiry);

// 		if (data->ray.raydirx < 0)
// 		{
// 			data->ray.stepx = -1;
// 			data->ray.sidedx = (data->player.posx - data->ray.mapx) * data->ray.deltadx;
// 		}
// 		else
// 		{
// 			data->ray.stepx = 1;
// 			data->ray.sidedx = (data->ray.mapx + 1.0 - data->player.posx) * data->ray.deltadx;
// 			// printf("the sidedx here be: %f\n", data->ray.sidedx);
// 		}
// 		if (data->ray.raydiry < 0)
// 		{
// 			// printf("Is it coming in here, the bastard?\n");
// 			// return ;
// 			data->ray.stepy = -1;
// 			data->ray.sidedy = (data->player.posy - data->ray.mapy) * data->ray.deltady;
// 			// printf("data->ray.sidedy[%f] = (data->player.posy[%f] - data->ray.mapy[%d]) * data->ray.deltady[%f]\n", data->ray.sidedy, data->player.posy, data->ray.mapy, data->ray.deltady);
// 			// printf("the raysidedy here be: %f  \n", data->ray.sidedy);
// 			// return ;
// 		}
// 		else
// 		{
// 			data->ray.stepy = 1;
// 			data->ray.sidedy = (data->ray.mapy + 1.0 - data->player.posy) * data->ray.deltady;
// 		}
// 		while (data->ray.hit == 0)
// 		{
// 			// printf("the sidedx here be: %f\n", data->ray.sidedx);
// 			// printf("the sidedy here be: %f\n", data->ray.sidedy);
// 			// return ;
// 			if (data->ray.sidedx < data->ray.sidedy) //I do believe it should come in here but it does not because sidedy is 0
// 			{
// 				data->ray.sidedx += data->ray.deltadx;
// 				data->ray.mapx += data->ray.stepx;
// 				data->ray.side = 0;
// 			}
// 			else
// 			{
// 				// printf("Is it coming in here, the bastard?\n");
// 				// return ;
// 				data->ray.sidedy += data->ray.deltady;
// 				data->ray.mapy += data->ray.stepy;
// 				data->ray.side = 1;
// 			}
// 			if (data->maparr[data->ray.mapy][data->ray.mapx] > 0)
// 				data->ray.hit = 1;
// 		}
// 		if (data->ray.side == 0)
// 		{
// 			data->ray.walldist = (data->ray.mapx - data->player.posx + (1.0 - data->ray.stepx) / 2.0) / data->ray.raydirx;
// 			// printf("wall distance %f = (data->ray.mapx %d- data->player.posx %f+ (1 - data->ray.stepx)%f / 2) / data->ray.raydirx%f", data->ray.walldist, data->ray.mapx, data->player.posx, (double)data->ray.stepx, data->ray.raydirx);
// 		}
// 		else
// 		{
// 			data->ray.walldist = ((data->ray.mapy - data->player.posy + (1.0 - data->ray.stepy) / 2.0) / data->ray.raydiry);
// 			// printf("wall distance %f = (data->ray.mapy [%d]- data->player.posy [%f]+ (1 - data->ray.stepy)[%d] / 2) / data->ray.raydiry[%f]\n", data->ray.walldist, data->ray.mapy, data->player.posy, data->ray.stepy, data->ray.raydiry);
// 			// return ;
// 		}
// 		data->ray.lineheight = (int)(data->resy / data->ray.walldist);
// 		// if (data->ray.lineheight < 0)
// 		// 	data->ray.lineheight *= -1;
// 		data->ray.drawstart = -(data->ray.lineheight) / 2.0 + data->resy / 2.0;
// 		if (data->ray.drawstart < 0)
// 			data->ray.drawstart = 0;
// 		data->ray.drawend = data->ray.lineheight / 2.0 + data->resy / 2.0;
// 		// if (data->ray.drawend < 0)
// 		// 	data->ray.drawend *= -1;
// 		if (data->ray.drawend >= data->resy)
// 			data->ray.drawend = data->resy - 1.0;
// 		// unsigned int colour = data->ceiling.colour;
// 		// if (data->ray.side == 1)
// 		// 	colour = colour / 2;
// 		int i = data->ray.drawstart;
// 		// printf("What is walldist: %f\n", data->ray.walldist);
// 		printf ("yar yar yar drawend%d\n", data->ray.drawend);
// 		printf("lineheight do be: %d\n", data->ray.lineheight);
// 		printf("Why why why drawstart %d\n", i);
// 		while (i < data->ray.drawend)
// 		{
// 			write(1, "1", 1);
// 			my_mlx_pixel_put(data, x, i, data->ceiling.colour);
// 			i++;
// 		}
// 		x++;
// 	}
// }