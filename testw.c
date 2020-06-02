/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testw.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/01 11:58:14 by tmullan       #+#    #+#                 */
/*   Updated: 2020/05/28 10:35:18 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

typedef struct	s_data 
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int colour)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = colour;
}

int		main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		len;
	int		i;
	int		x;
	int		y;

	x = 5;
	y = 5;
	i = 0;
	len = 500;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 600, 600, "mumyer");
	
	img.img = mlx_new_image(mlx, 600, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	//TRIANGLE
	while (i <= len)
	{
		my_mlx_pixel_put(&img, x, y, 0x000000FF);
		x++;
		i++;
		if (i == len)
		{
			x = 5;
			len--;
			y++;
			i = 0;
		}
	}

	// BIG BLUE SQUARE YO
	// while (i <= len)
	// {
	// 	my_mlx_pixel_put(&img, x, y, 0x000000FF);
	// 	x++;
	// 	i++;
	// 	if (i == len && y != x)
	// 	{
	// 		x = 5;
	// 		y++;
	// 		i = 0;
	// 	}
	// }

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	mlx_loop(mlx);
	return (0);
}
