/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_start.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 14:38:05 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/08 17:09:00 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		my_mlx_pixel_put(t_data *data, int x, int y, int colour)
{
	char	*dst;

	dst = data->mlx.addr + (y * data->mlx.linelen + x * (data->mlx.bpp / 8));
	*(unsigned int*)dst = colour;
}

int			frame_update(t_data *data)
{
	mlx_sync(1, data->mlx.img);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win,
		data->mlx.img, 0, 0);
	mlx_sync(3, data->mlx.mlx_win);
	return (0);
}

void		rotate(t_data *data)
{ // This shit is just tripping balls
	if (data->ray.key[4] == 1)
	{
		double oldirx = data->player.dirx;
		data->player.dirx = data->player.dirx * cos(-data->ray.rotspeed) - data->player.diry * sin(-data->ray.rotspeed);
		data->player.diry = oldirx * sin(-data->ray.rotspeed) + data->player.diry * cos(-data->ray.rotspeed);
		double oldplanex = data->player.planex;
		data->player.planex = data->player.planex * cos(-data->ray.rotspeed) - data->player.planey * sin(-data->ray.rotspeed);
		data->player.planey = oldplanex * sin(-data->ray.rotspeed) + data->player.planey * cos(-data->ray.rotspeed);
	}
	if (data->ray.key[5] == 1) //Left-rotate
	{
		double oldirx = data->player.dirx;
		data->player.dirx = data->player.dirx * cos(data->ray.rotspeed) - data->player.diry * sin(data->ray.rotspeed);
		data->player.diry = oldirx * sin(data->ray.rotspeed) + data->player.diry * cos(data->ray.rotspeed);
		double oldplanex = data->player.planex;
		data->player.planex = data->player.planex * cos(data->ray.rotspeed) - data->player.planey * sin(data->ray.rotspeed);
		data->player.planey = oldplanex * sin(data->ray.rotspeed) + data->player.planey * cos(data->ray.rotspeed);
	}
	// raycaster(data);
}

int			movement(t_data *data)
{
	if (data->ray.key[0] == 1)
	{
		if (data->maparr[(int)(data->player.posy + data->player.diry * data->ray.mspeed)][(int)data->player.posx] != '1')
			data->player.posy += (data->player.diry * data->ray.mspeed);
		if (data->maparr[(int)data->player.posy][(int)(data->player.posx + data->player.dirx * data->ray.mspeed)] != '1')
			data->player.posx += (data->player.dirx * data->ray.mspeed);
		// raycaster(data);
	} //WHY DOESN'T == '0' WORK!?!? will printf this later
	if (data->ray.key[1] == 1)
	{
		if (data->maparr[(int)(data->player.posy - data->player.diry * data->ray.mspeed)][(int)data->player.posx] != '1')
			data->player.posy -= (data->player.diry * data->ray.mspeed);
		if (data->maparr[(int)data->player.posy][(int)(data->player.posx - data->player.dirx * data->ray.mspeed)] != '1')
			data->player.posx -= (data->player.dirx * data->ray.mspeed);
		// raycaster(data);
	}
	if (data->ray.key[2] == 1)
	{
		if (data->maparr[(int)(data->player.posy - data->player.planey * data->ray.mspeed)][(int)data->player.posx] != '1')
			data->player.posy -= (data->player.planey * data->ray.mspeed);
		if (data->maparr[(int)data->player.posy][(int)(data->player.posx - data->player.planex * data->ray.mspeed)] != '1')
			data->player.posx -= (data->player.planex * data->ray.mspeed);
		// raycaster(data);
	}
	if (data->ray.key[3] == 1)
	{
		if (data->maparr[(int)(data->player.posy + data->player.planey * data->ray.mspeed)][(int)data->player.posx] != '1')
			data->player.posy += (data->player.planey * data->ray.mspeed);
		if (data->maparr[(int)data->player.posy][(int)(data->player.posx + data->player.planex * data->ray.mspeed)] != '1')
			data->player.posx += (data->player.planex * data->ray.mspeed);
		// raycaster(data);
	}
	if (data->ray.key[4] == 1 || data->ray.key[5] == 1)
		rotate(data);
	// raycaster(data);
	// data->ray.key = 0; Lifting the key should be enough
	return (0);
}

int			keypressed(int keycode, t_data *data)
{
	if (keycode == 13)
	{
		data->ray.key[0] = 1;
		printf("AVANTI TUTTA DIOCANEEE\n");
	}
	if (keycode == 1)
	{
		data->ray.key[1] = 1;
		printf("FAI RETROMARCIA CE STANNO E GUARDIE\n");
	}
	if (keycode == 0)
	{
		data->ray.key[2] = 1;
		printf("RIPARTIAMO DALLA SINISTRA\n");
	}
	if (keycode == 2)
	{
		data->ray.key[3] = 1;
		printf("SE TU DALL'ALTOPIANO GUARDI IL MARE\n");
	}
	if (keycode == 123)
	{
		data->ray.key[4] = 1;
		printf("GIRA LA ROTA BIMBO\n");
	}
	if (keycode == 124)
		data->ray.key[5] = 1;
	movement(data);
	return (0);
}

int			keyreleased(int keycode, t_data *data)
{
	if (keycode == 13)
		data->ray.key[0] = 0;
	if (keycode == 1)
		data->ray.key[1] = 0;
	if (keycode == 0)
		data->ray.key[2] = 0;
	if (keycode == 2)
		data->ray.key[3] = 0;
	if (keycode == 123)
		data->ray.key[4] = 0;
	if (keycode == 124)
		data->ray.key[5] = 0;
	return (0);
}

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
		if (data->ray.side == 0)
			data->ray.walldist = (data->ray.mapx - data->player.posx + (1. - data->ray.stepx) / 2.) / data->ray.raydirx;
		else
			data->ray.walldist = (data->ray.mapy - data->player.posy + (1. - data->ray.stepy) / 2.) / data->ray.raydiry;
		//Calculate height of line to draw
		data->ray.lineheight = (int)(data->resy / data->ray.walldist);
		//Calculate lowest and highest pixel
		data->ray.drawstart = -data->ray.lineheight / 2 + data->resy / 2;
		if (data->ray.drawstart < 0)
			data->ray.drawstart = 0;
		data->ray.drawend = data->ray.lineheight / 2 + data->resy / 2;
		if (data->ray.drawend >= data->resy)
			data->ray.drawend = data->resy;
		// data->ray.drawend = data->resy - 1; Check later if not using this causes issues
		//ACtually drawing
		unsigned int colour = 0x0000FF;
		if (data->ray.side == 1)
			colour = 0xFFFFFF;
		int i = 0;
		while (i < data->ray.drawstart)
		{
			my_mlx_pixel_put(data, x, i, data->ceiling.colour);
			i++;
		}
		while (data->ray.drawstart <= data->ray.drawend)
		{
			my_mlx_pixel_put(data, x, data->ray.drawstart, colour);
			data->ray.drawstart++;
		}
		while (data->ray.drawend < data->resy)
		{
			my_mlx_pixel_put(data, x, data->ray.drawend, data->floor.colour);
			data->ray.drawend++;
		}
		x++;
		// mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win,
		// 	data->mlx.img, 0, 0);
		// printf("Walldist = [%f] || mapx,y [%d][%d] || stepx,y [%d][%d] || raydirx,y [%f][%f] || posx, y [%f][%f]\nDeltadx, y = [%f][%f] || sidedx, y [%f][%f]\n", data->ray.walldist,
		// 		data->ray.mapx, data->ray.mapy, data->ray.stepx, data->ray.stepy, data->ray.raydirx, data->ray.raydiry, data->player.posx, data->player.posy, data->ray.deltadx, data->ray.deltady, data->ray.sidedx, data->ray.sidedy);
	}
	frame_update(data);
	data->ray.frame++;
	return (0);
}

void		mlx_start(t_data *data)
{
	data->mlx.mlx = mlx_init();
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, data->resx,
			data->resy, "mumyer");

	data->mlx.img = mlx_new_image(data->mlx.mlx, data->resx, data->resy);

	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bpp,
			&data->mlx.linelen, &data->mlx.endian);

	raycaster(data);
	mlx_hook(data->mlx.mlx_win, 02, 1L<<0, keypressed, data);
	mlx_hook(data->mlx.mlx_win, 03, 1L<<1, keyreleased, data);
	mlx_loop_hook(data->mlx.mlx, raycaster, data);
	mlx_loop(data->mlx.mlx);
}
