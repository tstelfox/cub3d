/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 18:13:18 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/18 11:55:05 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		store_coord(t_data *data, int y, int x, int i)
{
	data->sprite[i].x = (double)(x + 0.5);
	data->sprite[i].y = (double)(y + 0.5);
}

void		sprites_coord(t_data *data)
{
	t_thijs		*sprites;
	int			y;
	int			x;
	int			i;

	x = 0;
	y = 0;
	i = 0;
	sprites = malloc(sizeof(t_thijs) * (data->spritenum + 1));
	data->sprite = sprites;
	while (data->maparr[y])
	{
		x = 0;
		while (data->maparr[y][x])
		{
			if (data->maparr[y][x] == '2')
			{
				store_coord(data, y, x, i); // Store the correct coordinates for every spriteboi
				printf("Coordinates of the sprite are: %f %f\n", data->sprite[i].x, data->sprite[i].y);
				i++;
			}
			x++;
		}
		y++;
	}
}

void		count_sprites(t_data *data)
{
	int i;
	int thijs;

	thijs = 0;
	i = 0;
	while (data->maptemp[i])
	{
		if (data->maptemp[i] == '2')
			thijs++;
		i++;
	}
	data->spritenum = thijs;
}

void		sprites_init(t_data *data)
{
	count_sprites(data);
	sprites_coord(data);
}
