/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_draw.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 15:44:25 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/22 22:26:13 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		sprite_draw(t_data *data)
{
	int i;

	i = 0;
	// printf("number of sprites is %d\n", data->spritenum);
	// printf("Farthest sprite is at x[%f] y[%f]", data->sprite[i].x, data->sprite[i].y);
	while (i < data->spritenum)
	{
		data->casts.spritex = data->sprite[i].x - data->player.posx;
		data->casts.spritey = data->sprite[i].y - data->player.posy;
		// printf("The spritex and spritey are %f %f\n", data->casts.spritex, data->casts.spritey);

		data->casts.invdet = 1.0 / (data->player.planex * data->player.diry - data->player.dirx * data->player.planey);
		// printf("What's this invdet shit? %f = planex[%f] * diry[%f] - dirx[%f] * planey[%f]\n", data->casts.invdet, data->player.planex, data->player.diry, data->player.dirx, data->player.planey);
		data->casts.tranx = data->casts.invdet * (data->player.diry * data->casts.spritex - data->player.dirx * data->casts.spritey);
		data->casts.trany = data->casts.invdet * (-data->player.planey * data->casts.spritex + data->player.planex * data->casts.spritey);
		// printf("transformy is here %f = invdet[%f] * (planey[%f] * spritex[%f] + planex[%f] * spritey[%f]\n", data->casts.trany, data->casts.invdet, data->player.planey, data->casts.spritex, data->player.planex, data->casts.spritey);
		// printf("transformx is here %f\n", data->casts.tranx);

		data->casts.screenx = (int)((data->resx / 2) * (1 + data->casts.tranx / data->casts.trany));
		// printf("what about screenx? %d\n", data->casts.screenx);

		//calculate height of sprite on screen
		data->casts.spriteh = abs((int)(data->resy / data->casts.trany));
		//Lowest and heighest pixel to fill in current stripe
		data->casts.dstarty = -data->casts.spriteh / 2 + data->resy / 2;
		if (data->casts.dstarty < 0)
			data->casts.dstarty = 0;
		data->casts.dendy = data->casts.spriteh / 2 + data->resy / 2;
		if (data->casts.dendy >= data->resy)
			data->casts.dendy = data->resy - 1;
		//width of sprite
		data->casts.spritew = abs((int)(data->resy / data->casts.trany));
		data->casts.dstartx = -data->casts.spritew / 2 + data->casts.screenx;
		// printf("sprite height is here: %d\n", data->casts.spriteh);
		// printf("sprite width is here: %d\n", data->casts.spritew);
		if (data->casts.dstartx < 0)
			data->casts.dstartx = 0;
		// printf("drawstart for x is here: %d\n", data->casts.dstartx);
		data->casts.dendx = data->casts.spritew / 2 + data->casts.screenx;
		if (data->casts.dendx >= data->resx)
			data->casts.dendx = data->resx - 1;

		//Now for the drawing
		int x;
		int y;
		// y = data->casts.dstarty;
		x = data->casts.dstartx;
		// printf("Right yo what is x doin [%d]\n", x);
		// printf("Is dendx too small?%d\n", data->casts.dendx);
		// printf("Right yo what is y doin [%d]\n", y);
		while (x < data->casts.dendx)
		{
			// printf("Is dendx too small?%d\n", data->casts.dendx);
			// printf("does this rotation go? %d\n", x);
			int textx = (int)(256 * (x - (-data->casts.spritew / 2 + data->casts.screenx))
					* data->spt.width / data->casts.spritew) / 256;
			// printf("The buffer is %f\n", data->casts.zbuffer[x]);
			// printf("The transformy is %f\n", data->casts.trany);
			y = data->casts.dstarty;
			if (data->casts.trany > 0 && x > 0 && x < data->resx && data->casts.trany < data->casts.zbuffer[x])
			{
				while (y < data->casts.dendy)
				{
					// printf("does this rotation go? %d\n", y);
					// printf("Is dendy too small?%d\n", data->casts.dendy);
					int d = (y) * 256 - data->resy * 128 + data->casts.spriteh * 128;
					int texy = ((d * data->spt.height) / data->casts.spriteh) / 256;
					data->texcol.colour = colour_getter(data, textx, texy, 42);
					// if ((colour & 0x00FFFFFF) != 0)
					if (data->texcol.colour && data->texcol.t_rgb.a == 0)
						my_mlx_pixel_put(data, x, y, data->texcol.colour);
					y++;
				}
			}
			x++;
		}
		i++;
	}
}
