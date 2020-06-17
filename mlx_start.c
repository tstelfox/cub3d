/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_start.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 14:38:05 by tmullan       #+#    #+#                 */
/*   Updated: 2020/06/17 14:49:38 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int colour)
{
	char	*dst;

	dst = data->mlx.addr + (y * data->mlx.linelen + x * (data->mlx.bpp / 8));
	*(unsigned int*)dst = colour;
}

void		mlx_start(t_data *data)
{
	int x = 10;
	data->mlx.mlx = mlx_init();
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, data->resx,
			data->resy, "mumyer");

	data->mlx.img = mlx_new_image(data->mlx.mlx, data->resx, data->resy);

	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bpp,
			&data->mlx.linelen, &data->mlx.endian);
	while (x < 1000)
	{
		my_mlx_pixel_put(data, 10, x, 0x00FF0000);
		x++;
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win,
			data->mlx.img, 0, 0);
	mlx_loop(data->mlx.mlx);
}
