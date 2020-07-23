/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 18:13:18 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/23 12:36:48 by tmullan       ########   odam.nl         */
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
				// printf("Coordinates of the sprite are: %f %f\n", data->sprite[i].x, data->sprite[i].y);
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

void		sprite_order(t_data *data)
{
	int		i;
	int		k;
	t_thijs	temp;

	i = 0;
	while (i < data->spritenum)
	{
		data->sprite[i].dist = ((data->player.posx - data->sprite[i].x) * (data->player.posx - data->sprite[i].x) +
			(data->player.posy - data->sprite[i].y) * (data->player.posy - data->sprite[i].y));
		i++;
	}
	i = 0;
	while (i < data->spritenum - 1)
	{
		k = 0;
		while (k < data->spritenum - i - 1)
		{
			if (data->sprite[k].dist < data->sprite[k + 1].dist)
			{
				temp = data->sprite[k];
				// printf("the temp dist here is %f\n", temp.dist);
				data->sprite[k] = data->sprite[k + 1];
				// printf("the old dist here is %f\n", data->sprite[k + 1].dist);
				data->sprite[k + 1] = temp;
				// printf("the new dist here is %f\n", data->sprite[k + 1].dist);
			}
			k++;
		}
		i++;
	}
	// for (i = 0; i < data->spritenum; i++)
	// {
	// 	printf("The ordered x and y of the sprites do be [%d]: %f %f\n", i, data->sprite[i].x, data->sprite[i].y);
	// 	printf("The ordered dist of the sprites do be [%d]: %f\n", i, data->sprite[i].dist);
	// }
}
