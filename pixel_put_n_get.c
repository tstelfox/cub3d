/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pixel_put_n_get.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/30 15:27:03 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/30 15:27:29 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			my_mlx_pixel_put(t_data *data, int x, int y, int colour)
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
		dst = data->sprite_addr + ((y * data->spt.linelen) +
				(x * (data->spt.bpp / 8)));
		return (*(unsigned int*)dst);
	}
	dst = data->tex[compass] + ((y * data->walls[compass].linelen) +
		(x * (data->walls[compass].bpp / 8)));
	return (*(unsigned int*)dst);
}
