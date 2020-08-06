/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/25 18:45:59 by tmullan       #+#    #+#                 */
/*   Updated: 2020/08/06 13:27:20 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	image_colour(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->mlx.addr + ((y * data->mlx.linelen) +
		(x * (data->mlx.bpp / 8)));
	return (*(unsigned int*)dst);
}

void			char_to_int(unsigned char *header, int n)
{
	header[0] = (unsigned char)(n);
	header[1] = (unsigned char)(n >> 8);
	header[2] = (unsigned char)(n >> 16);
	header[3] = (unsigned char)(n >> 24);
}

void			bmpcontent(t_data *data)
{
	int				x;
	int				y;
	t_colour		colour;
	unsigned char	pad;

	pad = 0;
	y = data->resy - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < data->resx)
		{
			colour.colour = image_colour(data, x, y);
			write(data->bmp, &colour.colour, 3);
			write(data->bmp, &pad, 1);
			x++;
		}
		y--;
	}
}

void			bmpheader(t_data *data, int filesize)
{
	int				i;
	unsigned char	header[54];

	i = 0;
	while (i < 54)
	{
		header[i] = (unsigned char)(0);
		i++;
	}
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	char_to_int(header + 2, filesize);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	char_to_int(header + 18, data->resx);
	char_to_int(header + 22, data->resy);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(32);
	write(data->bmp, header, 54);
}

void			screenshotter(t_data *data)
{
	int filesize;

	data->bmp = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	filesize = data->resx * data->resy * 4 + 54;
	if (data->resx > 1000000 || data->resy > 1000000)
		bad_input(data, "Error\nBmp too large you gonna blow this shit\n");
	bmpheader(data, filesize);
	bmpcontent(data);
	close(data->bmp);
	quit(data);
	return ;
}
