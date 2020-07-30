/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/30 15:31:42 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/30 15:32:22 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				keypressed(int keycode, t_data *data)
{
	if (keycode == 13)
		data->ray.key[0] = 1;
	if (keycode == 1)
		data->ray.key[1] = 1;
	if (keycode == 0)
		data->ray.key[2] = 1;
	if (keycode == 2)
		data->ray.key[3] = 1;
	if (keycode == 123)
		data->ray.key[4] = 1;
	if (keycode == 124)
		data->ray.key[5] = 1;
	if (keycode == 53)
		exit(0);
	return (0);
}

int				keyreleased(int keycode, t_data *data)
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

int				frames(t_data *data)
{
	int i;

	i = 0;
	while (i < 6)
	{
		if (data->ray.key[i] != 0)
			movement(data);
		i++;
	}
	return (0);
}
