/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/30 15:28:35 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/30 17:22:52 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			rotate_left(t_data *data, double oldirx, double oldplanex)
{
	oldirx = data->player.dirx;
	data->player.dirx = data->player.dirx * cos(-data->ray.rotspeed) -
		data->player.diry * sin(-data->ray.rotspeed);
	data->player.diry = oldirx * sin(-data->ray.rotspeed) +
		data->player.diry * cos(-data->ray.rotspeed);
	oldplanex = data->player.planex;
	data->player.planex = data->player.planex * cos(-data->ray.rotspeed) -
		data->player.planey * sin(-data->ray.rotspeed);
	data->player.planey = oldplanex * sin(-data->ray.rotspeed) +
		data->player.planey * cos(-data->ray.rotspeed);
}

void			rotate_right(t_data *data, double oldirx, double oldplanex)
{
	oldirx = data->player.dirx;
	data->player.dirx = data->player.dirx * cos(data->ray.rotspeed) -
		data->player.diry * sin(data->ray.rotspeed);
	data->player.diry = oldirx * sin(data->ray.rotspeed) +
		data->player.diry * cos(data->ray.rotspeed);
	oldplanex = data->player.planex;
	data->player.planex = data->player.planex * cos(data->ray.rotspeed) -
		data->player.planey * sin(data->ray.rotspeed);
	data->player.planey = oldplanex * sin(data->ray.rotspeed) +
		data->player.planey * cos(data->ray.rotspeed);
}

void			walking(t_data *data)
{
	if (data->ray.key[0] == 1)
	{
		if (data->maparr[(int)(data->player.posy + data->player.diry *
				data->ray.mspeed)][(int)data->player.posx] == '0')
			data->player.posy += (data->player.diry * data->ray.mspeed);
		if (data->maparr[(int)data->player.posy][(int)(data->player.posx
				+ data->player.dirx * data->ray.mspeed)] == '0')
			data->player.posx += (data->player.dirx * data->ray.mspeed);
	}
	if (data->ray.key[1] == 1)
	{
		if (data->maparr[(int)(data->player.posy - data->player.diry *
				data->ray.mspeed)][(int)data->player.posx] == '0')
			data->player.posy -= (data->player.diry * data->ray.mspeed);
		if (data->maparr[(int)data->player.posy][(int)(data->player.posx
				- data->player.dirx * data->ray.mspeed)] == '0')
			data->player.posx -= (data->player.dirx * data->ray.mspeed);
	}
}

void			strafing(t_data *data)
{
	if (data->ray.key[2] == 1)
	{
		if (data->maparr[(int)(data->player.posy - data->player.planey *
				data->ray.mspeed)][(int)data->player.posx] == '0')
			data->player.posy -= (data->player.planey * data->ray.mspeed);
		if (data->maparr[(int)data->player.posy][(int)(data->player.posx
				- data->player.planex * data->ray.mspeed)] == '0')
			data->player.posx -= (data->player.planex * data->ray.mspeed);
	}
	if (data->ray.key[3] == 1)
	{
		if (data->maparr[(int)(data->player.posy + data->player.planey *
				data->ray.mspeed)][(int)data->player.posx] == '0')
			data->player.posy += (data->player.planey * data->ray.mspeed);
		if (data->maparr[(int)data->player.posy][(int)(data->player.posx
				+ data->player.planex * data->ray.mspeed)] == '0')
			data->player.posx += (data->player.planex * data->ray.mspeed);
	}
}

int				movement(t_data *data)
{
	double oldirx;
	double oldplanex;

	oldirx = 0;
	oldplanex = 0;
	if (data->ray.key[0] == 1 || data->ray.key[1] == 1)
		walking(data);
	if (data->ray.key[2] == 1 || data->ray.key[3] == 1)
		strafing(data);
	if (data->ray.key[4] == 1)
		rotate_left(data, oldirx, oldplanex);
	if (data->ray.key[5] == 1)
		rotate_right(data, oldirx, oldplanex);
	raycaster(data);
	return (0);
}
