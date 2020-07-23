/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_start.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 14:38:05 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/23 13:15:26 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		my_mlx_pixel_put(t_data *data, int x, int y, int colour)
{
	char	*dst;

	dst = data->mlx.addr + (y * data->mlx.linelen + x * (data->mlx.bpp / 8));
	*(unsigned int*)dst = colour;
}

unsigned int	colour_getter(t_data *data, int x, int y, int compass)
{
	char	*dst;
	if (compass == 42)
	{
		dst = data->sprite_addr + ((y * data->spt.linelen) + (x * (data->spt.bpp / 8)));
		return (*(unsigned int*)dst);
	}
	dst = data->tex[compass] + ((y * data->walls[compass].linelen) + (x * (data->walls[compass].bpp / 8)));
	return (*(unsigned int*)dst);
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
{
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
		// if (data->maparr[(int)(data->player.posy + data->player.diry * data->ray.mspeed)][(int)data->player.posx] != '1' && data->maparr[(int)(data->player.posy + data->player.diry * data->ray.mspeed)][(int)data->player.posx] != '2')
		if (data->maparr[(int)(data->player.posy + data->player.diry * data->ray.mspeed)][(int)data->player.posx] == '0')
			data->player.posy += (data->player.diry * data->ray.mspeed);
		// if (data->maparr[(int)data->player.posy][(int)(data->player.posx + data->player.dirx * data->ray.mspeed)] != '1' && data->maparr[(int)data->player.posy][(int)(data->player.posx + data->player.dirx * data->ray.mspeed)] != '2')
		if (data->maparr[(int)data->player.posy][(int)(data->player.posx + data->player.dirx * data->ray.mspeed)] == '0')
			data->player.posx += (data->player.dirx * data->ray.mspeed);
	}
	if (data->ray.key[1] == 1)
	{
		// if (data->maparr[(int)(data->player.posy - data->player.diry * data->ray.mspeed)][(int)data->player.posx] != '1' && data->maparr[(int)(data->player.posy - data->player.diry * data->ray.mspeed)][(int)data->player.posx] != '2')
		if (data->maparr[(int)(data->player.posy - data->player.diry * data->ray.mspeed)][(int)data->player.posx] == '0')
			data->player.posy -= (data->player.diry * data->ray.mspeed);
		// if (data->maparr[(int)data->player.posy][(int)(data->player.posx - data->player.dirx * data->ray.mspeed)] != '1' && data->maparr[(int)data->player.posy][(int)(data->player.posx - data->player.dirx * data->ray.mspeed)] != '2')
		if (data->maparr[(int)data->player.posy][(int)(data->player.posx - data->player.dirx * data->ray.mspeed)] == '0')
			data->player.posx -= (data->player.dirx * data->ray.mspeed);
	}
	if (data->ray.key[2] == 1)
	{
		// if (data->maparr[(int)(data->player.posy - data->player.planey * data->ray.mspeed)][(int)data->player.posx] != '1' && data->maparr[(int)(data->player.posy - data->player.planey * data->ray.mspeed)][(int)data->player.posx] != '2')
		if (data->maparr[(int)(data->player.posy - data->player.planey * data->ray.mspeed)][(int)data->player.posx] == '0')
			data->player.posy -= (data->player.planey * data->ray.mspeed);
		// if (data->maparr[(int)data->player.posy][(int)(data->player.posx - data->player.planex * data->ray.mspeed)] != '1' && data->maparr[(int)data->player.posy][(int)(data->player.posx - data->player.planex * data->ray.mspeed)] != '2')
		if (data->maparr[(int)data->player.posy][(int)(data->player.posx - data->player.planex * data->ray.mspeed)] == '0')
			data->player.posx -= (data->player.planex * data->ray.mspeed);
	}
	if (data->ray.key[3] == 1)
	{
		// if (data->maparr[(int)(data->player.posy + data->player.planey * data->ray.mspeed)][(int)data->player.posx] != '1' && data->maparr[(int)(data->player.posy + data->player.planey * data->ray.mspeed)][(int)data->player.posx] != '2')
		if (data->maparr[(int)(data->player.posy + data->player.planey * data->ray.mspeed)][(int)data->player.posx] == '0')
			data->player.posy += (data->player.planey * data->ray.mspeed);
		// if (data->maparr[(int)data->player.posy][(int)(data->player.posx + data->player.planex * data->ray.mspeed)] != '1' && data->maparr[(int)data->player.posy][(int)(data->player.posx + data->player.planex * data->ray.mspeed)] != '2')
		if (data->maparr[(int)data->player.posy][(int)(data->player.posx + data->player.planex * data->ray.mspeed)] == '0')
			data->player.posx += (data->player.planex * data->ray.mspeed);
	}
	if (data->ray.key[4] == 1 || data->ray.key[5] == 1)
		rotate(data);
	return (0);
}

int			keypressed(int keycode, t_data *data)
{
	if (keycode == 13)
	{
		data->ray.key[0] = 1;
		// printf("AVANTI TUTTA DIOCANEEE\n");
	}
	if (keycode == 1)
	{
		data->ray.key[1] = 1;
		// printf("FAI RETROMARCIA CE STANNO E GUARDIE\n");
	}
	if (keycode == 0)
	{
		data->ray.key[2] = 1;
		// printf("RIPARTIAMO DALLA SINISTRA\n");
	}
	if (keycode == 2)
	{
		data->ray.key[3] = 1;
		// printf("SE TU DALL'ALTOPIANO GUARDI IL MARE\n");
	}
	if (keycode == 123)
	{
		data->ray.key[4] = 1;
		// printf("GIRA LA ROTA BIMBO\n");
	}
	if (keycode == 124)
		data->ray.key[5] = 1;
	if (keycode == 53)
		exit(0);
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

void		init_texture(t_data *data)
{
	int		img_width;
	int		img_height;
	int		i;

	i = 0;
	while (i < 4)
	{
		data->walls[i].img = mlx_xpm_file_to_image(data->mlx.mlx, data->tex[i], &img_width, &img_height);
		data->walls[i].height = img_height;
		data->walls[i].width = img_width;
		data->tex[i] = mlx_get_data_addr(data->walls[i].img, &data->walls[i].bpp,
				&data->walls[i].linelen, &data->walls[i].endian);
		i++;
	}
}

void		addr_sprite(t_data *data)
{
	int		img_width;
	int		img_height;

	data->spt.img = mlx_xpm_file_to_image(data->mlx.mlx, data->sprite_addr, &img_width, &img_height);
	data->spt.height = img_height;
	data->spt.width = img_width;
	data->sprite_addr = mlx_get_data_addr(data->spt.img, &data->spt.bpp,
				&data->spt.linelen, &data->spt.endian);
}

void		mlx_start(t_data *data)
{
	data->mlx.mlx = mlx_init();
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, data->resx,
			data->resy, "mumyer");
	data->mlx.img = mlx_new_image(data->mlx.mlx, data->resx, data->resy);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bpp,
			&data->mlx.linelen, &data->mlx.endian);
	init_texture(data);
	addr_sprite(data);
	raycaster(data);
	mlx_hook(data->mlx.mlx_win, 02, 1L<<0, keypressed, data);
	mlx_hook(data->mlx.mlx_win, 03, 1L<<1, keyreleased, data);
	mlx_hook(data->mlx.mlx_win, 17,1L<<2, quit, data);
	mlx_loop_hook(data->mlx.mlx, raycaster, data);
	mlx_loop(data->mlx.mlx);
}
