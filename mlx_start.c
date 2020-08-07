/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_start.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 14:38:05 by tmullan       #+#    #+#                 */
/*   Updated: 2020/08/07 14:22:47 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				frame_update(t_data *data)
{
	if (data->save == 1)
		screenshotter(data);
	mlx_sync(1, data->mlx.img);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win,
		data->mlx.img, 0, 0);
	mlx_sync(3, data->mlx.mlx_win);
	return (0);
}

void			init_texture(t_data *data)
{
	int		img_width;
	int		img_height;
	int		i;

	i = 0;
	while (i < 4)
	{
		data->walls[i].img = mlx_xpm_file_to_image(data->mlx.mlx, data->tex[i],
			&img_width, &img_height);
		if (data->walls[i].img == NULL)
			bad_input("Error\nFuck you for testing this\n");
		data->walls[i].height = img_height;
		data->walls[i].width = img_width;
		free(data->tex[i]);
		data->tex[i] = mlx_get_data_addr(data->walls[i].img, &data->walls[i].bpp
			, &data->walls[i].linelen, &data->walls[i].endian);
		i++;
	}
}

void			addr_sprite(t_data *data)
{
	int		img_width;
	int		img_height;

	data->spt.img = mlx_xpm_file_to_image(data->mlx.mlx, data->sprite_addr,
		&img_width, &img_height);
	if (data->spt.img == NULL)
		bad_input("Error\nFuck you for testing this\n");
	data->spt.height = img_height;
	data->spt.width = img_width;
	free(data->sprite_addr);
	data->sprite_addr = mlx_get_data_addr(data->spt.img, &data->spt.bpp,
				&data->spt.linelen, &data->spt.endian);
}

void			mlx_start(t_data *data)
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
	mlx_hook(data->mlx.mlx_win, 02, 1L << 0, keypressed, data);
	mlx_hook(data->mlx.mlx_win, 03, 1L << 1, keyreleased, data);
	mlx_hook(data->mlx.mlx_win, 17, 1L << 2, quit, data);
	mlx_loop_hook(data->mlx.mlx, frames, data);
	mlx_loop(data->mlx.mlx);
}
